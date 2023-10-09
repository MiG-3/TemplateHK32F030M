#ifndef UTILS_SINGLETONE_HPP
#define UTILS_SINGLETONE_HPP

/* ����� ���������� ���������
*
* ����� ��������� ������ �������� ���� ��� � ��������� �������� TRealisation.
* ��� ������������� �������� ������� ���������� ����� ��������� ������ ��������
* ������������ � ����������� ����������, � Singletone �������� ��� friend.
*
* ������:
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
	// ��������� ���������� ����������� � �������� ������������
	// ����� ����� ��������� ����������� ����������� �������
    Singletone(const Singletone&);
    Singletone& operator = (const Singletone&);
protected:
    // ����������� � ���������� ��������� ������ �����������
    ~Singletone() {}
    Singletone() {}
public:
    // ��������� ������ �� ��������� �������-��������.
    static TRealisation& instance() {
        static TRealisation inst;
        return inst;
    }
};

#endif // UTILS_SINGLETONE_HPP
