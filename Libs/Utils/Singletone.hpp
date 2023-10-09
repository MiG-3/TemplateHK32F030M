#ifndef UTILS_SINGLETONE_HPP
#define UTILS_SINGLETONE_HPP

/* Класс реализации синглтона
*
* Класс наследник должен передать свой тип в шаблонный параметр TRealisation.
* Для невозможности создания второго экземпляра класс наследник должен объявить
* конструкторы и деструкторы приватными, а Singletone объявить как friend.
*
* Пример:
*
*  class TestSingletone : public Singletone<TestSingletone> {
*    private:
*        friend Singletone<TestSingletone>;
*
*        TestSingletone() : Singletone<TestSingletone>() {
*            ...
*        }
*
*        ~TestSingletone() {};
*    public:
*        void testMethod() {
*            ...
*        }
*
*  };
*
*  int main() {
*      TestSingletone& ts = TestSingletone::instanse();
*      ts.testMethod();
*      TestSingletone::instance().testMethod();
*      return 0;
*  }
*
*/

template<typename TRealisation>
class Singletone {
private:
	// Приватные копирующий конструктор и оператор присваивания
	// нужны чтобы исключить возможность копирования объекта
    Singletone(const Singletone&);
    Singletone& operator = (const Singletone&);
protected:
    // Конструктор и деструктор доступные только наследникам
    ~Singletone() {}
    Singletone() {}
public:
    // Получение ссылки на экземпляр объекта-синглтон.
    static TRealisation& instance() {
        static TRealisation inst;
        return inst;
    }
};

#endif // UTILS_SINGLETONE_HPP
