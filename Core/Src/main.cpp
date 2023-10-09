
#include <Drivers/HK32F030M_Wrapper/Gpio/Gpio.hpp>
#include <Drivers/HK32F030M_Wrapper/Timer/TimerList.hpp>
#include <Drivers/HK32F030M_Wrapper/Adc/AdcList.hpp>
#include <Drivers/HK32F030M_Wrapper/Uart/UartList.hpp>
#include <Drivers/HK32F030M_Wrapper/Eeprom/Eeprom.hpp>

using namespace Drivers::Gpio;
using namespace Drivers::Timer;
using namespace Drivers::Adc;
using namespace Drivers::Uart;

constexpr Gpio led1 {Port::GpioD, Pin::Pin1, Drivers::Gpio::Mode::Output, Speed::Low, OutputType::OpenDrain, Pull::None};
constexpr Gpio led2 {Port::GpioC, Pin::Pin7, Drivers::Gpio::Mode::Output, Speed::Low, OutputType::OpenDrain, Pull::None};
constexpr Gpio led3 {Port::GpioA, Pin::Pin2, Drivers::Gpio::Mode::Output, Speed::Low, OutputType::OpenDrain, Pull::None};

constexpr AdcParams adcParams = {
    .clkMode = ClockMode::Asynk,
    .continuousMode = false,
    .triggerEdge = TriggerEdge::Rising,
    .triggerSource =TriggerSources::Timer2TriggerOut,
    . alignment = DataAlignment::Right,
    .direction = ScanDirection::Upward
};
constexpr ChannelParams chParams [] {
    { Drivers::Adc::Channel::Channel4, SamplingTime::Cycle_239_5 },
    { Drivers::Adc::Channel::Channel_VrefInt, SamplingTime::Cycle_239_5 }
};
constexpr array_mapping<const ChannelParams> chParamsArr(chParams, arraysize(chParams));

constexpr UartParams uartParams = {
    .baudRate = 19200,
    .dataBits = DataBits::DB_8Bits,
    .stopBits = StopBits::One,
    .parity = Parity::None,
    .mode = Drivers::Uart::Mode::RxTx,
    .flowControl = HardwareFlowControl::None
};

uint8_t raw_buf[32];
buffer<uint8_t> buf(raw_buf, 32);


struct Settings {
 uint32_t version;
 char name[16];
};
Settings settings {};

int main() {
  auto& halTimer = TimerList::halTimebase();
  auto& adcTimer = TimerList::tim2();
  auto& adc = AdcList::adc();
  auto& uart =  UartList::uart1();

  halTimer.init();

  adc.init(adcParams, chParamsArr);
  adcTimer.init(2000);
  adcTimer.setTRGOUpdate();
  adcTimer.start();


  uart.init(uartParams);
  buf.push_back(0xAA);
  buf.push_back(0x55);

  led1.init(); led2.init(); led3.init();
  led1.low();  led2.high(); led3.high();
  constexpr uint32_t dl {200};

  adc.activateInterrupt(Drivers::IrqPriority::High);
  adc.startConversion();

  uint32_t cnt = 10;

  Drivers::Eeprom::instance().read(0, settings);

  while(1) {
    halTimer.delay(dl);
    led1.high(); led2.low(); led3.high();
    halTimer.delay(dl);
    led1.high(); led2.high(); led3.low();
    halTimer.delay(dl);
    led1.low();  led2.high(); led3.high();

    if(cnt) {uart.write(buf, 2); cnt--;}
  }
  return 0;
}
