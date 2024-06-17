#ifndef __PROGTEST__
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <climits>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <array>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <functional>
#include <iterator>
#include <compare>

class CDate
{
public:
    CDate                         ( int               y,
                                    int               m,
                                    int               d )
            : m_Y ( y ),
              m_M ( m ),
              m_D ( d )
    {
    }

    std::strong_ordering     operator <=>                  ( const CDate     & other ) const = default;

    friend std::ostream    & operator <<                   ( std::ostream    & os,
                                                             const CDate     & d )
    {
        return os << d . m_Y << '-' << d . m_M << '-' << d . m_D;
    }

private:
    int                      m_Y;
    int                      m_M;
    int                      m_D;
};
enum class ESortKey
{
    NAME,
    BIRTH_DATE,
    ENROLL_YEAR
};
#endif /* __PROGTEST__ */

std::string Gulas(const  std::string & name){
    if(name.empty()){
        return {};
    }
    std::string gulas;
    gulas.reserve(name.size());
    for (char ch : name) {
        if (ch != ' ') {
            gulas.push_back(static_cast<char>(std::tolower(ch)));
        }
    }
    std::sort(gulas.begin(), gulas.end());

    return gulas;

}

class CStudent
{
public:
    CStudent                      ( const std::string & name,
                                    const CDate     & born,
                                    int               enrolled ):m_NameStudent(name), m_BirthdayStudent(born), m_enrolledStudent(enrolled){

        m_GulasNameStudent = std::move(Gulas(name));
        std::stringstream ss(name);
        std::string word;
        while (ss >> word) {
            m_SetWordNameStudent.insert(Gulas(word));
        }

    }

    bool                     operator ==                   ( const CStudent  & other ) const{
        return (other.m_NameStudent == this->m_NameStudent && other.m_enrolledStudent == this->m_enrolledStudent && other.m_BirthdayStudent == this->m_BirthdayStudent);
    }
    bool                     operator !=                   ( const CStudent  & other ) const{
        return !(other == *this);
    }

    friend std::ostream& operator<<(std::ostream & os, const CStudent & bibochka){
        os<<bibochka.m_NameStudent<<" "<<bibochka.m_BirthdayStudent<<" "<<bibochka.m_enrolledStudent<<" "<<bibochka.m_NumberStudent;
        return os;
    }

    int get_StudentNumber()const{
        return m_NumberStudent;
    }
    const std::string & get_NameStudent()const{
        return m_NameStudent;
    };


    const std::set<std::string> & get_set()const{
        return m_SetWordNameStudent;
    }
    const std::string & get_Gulas()const{
        return m_GulasNameStudent;
    }

    CDate  get_BirthdayStudent()const{
        return m_BirthdayStudent;
    }

    int get_enrolledStudent()const{
        return m_enrolledStudent;
    };

    void set_Number(int number){
        m_NumberStudent = number;
    }

private:
    std::string m_NameStudent;
    int m_NumberStudent;
    CDate m_BirthdayStudent;
    int m_enrolledStudent;
    std::string m_GulasNameStudent;
    std::set<std::string> m_SetWordNameStudent;

};



enum class PatchType{
    None,
    NAME,
    BornBefore,
    BornAfter,
    EnrolledBefore,
    EnrolledAfter
};

struct CFilterSinglePatch{

    PatchType Type=PatchType::None;
    std::string Name;
    CDate Date_born;
    int Enroll_year=0;

    CFilterSinglePatch(const std::string &name, const CDate &data, int enroll, PatchType type)
            : Type(type), Name(name), Date_born(data), Enroll_year(enroll) {}

};
class CFilter
{
public:
    CFilter()
            :BB(INT32_MAX, INT32_MAX, INT32_MAX) ,BA(INT32_MIN, INT32_MIN, INT32_MIN),EA(INT32_MIN), EB(INT32_MAX)
    {}

    CFilter                & name                          ( const std::string & name ){
        names.insert(Gulas(name));
        return *this;
    }
    CFilter                & bornBefore                    ( const CDate     & date ){
            if(date<BB){
                BB = date;
            }
            return *this;
    }
    CFilter                & bornAfter                     ( const CDate     & date ){
        if(date>BA){
            BA = date;
        }
        return *this;
    }
    CFilter                & enrolledBefore                ( int               year ){
        if(year<EB){
            EB = year;
        }
        return *this;
    }
    CFilter                & enrolledAfter                 ( int               year ){
        if(year>EA){
            EA = year;
        }
        return *this;
    }


    bool spravny_filter()const{
        if(BB<=BA){return false;}
        if(EA>=EB){return false;}
        return true;
    }


    CDate getBB()const{
        return BB;
    }
    CDate getBA()const{
        return BA;
    }
    int getEA()const{
        return EA;
    }
    int getEB()const{
        return EB;
    }

    const std::set<std::string> getNames()const{
        return names;
    }


    bool empty_filter()const{
        if(BB == CDate(INT32_MAX,INT32_MAX,INT32_MAX) && BA==CDate(INT32_MIN,INT32_MIN,INT32_MIN) && EA == INT32_MIN && EB==INT32_MAX && names.empty()){
            return true;
        }
        return false;
    }
private:

    CDate BB;
    CDate BA;
    int EA ;
    int EB;
    std::set<std::string> names;
};













struct Sortpatch{
    ESortKey key;
    bool ascending;

    Sortpatch(ESortKey key,bool ascending ):key(key),ascending(ascending){}
};
class CSort
{
public:
    CSort                         ()=default;
    CSort                  & addKey                        ( ESortKey          key,
                                                             bool              ascending ){
        Sortpatch a(key, ascending);
        sortpatches.push_back(a);

        return *this;
    }
    bool EmptySort()const{
        return sortpatches.empty();
    }

    bool operator()(const CStudent& a, const CStudent& b) const {
        size_t size = sortpatches.size();

        for(size_t i = 0;i<size;i++){
            if(sortpatches[i].key == ESortKey::NAME){
                if(a.get_NameStudent() != b.get_NameStudent()){
                    if(sortpatches[i].ascending){
                        return a.get_NameStudent() < b.get_NameStudent();
                    }else{
                        return a.get_NameStudent() > b.get_NameStudent();
                    }
                }else{
                    continue;
                }
            }else if(sortpatches[i].key == ESortKey::BIRTH_DATE){
                if(a.get_BirthdayStudent() != b.get_BirthdayStudent()){
                    if(sortpatches[i].ascending){
                        return a.get_BirthdayStudent() < b.get_BirthdayStudent();
                    }else{
                        return a.get_BirthdayStudent() > b.get_BirthdayStudent();
                    }
                }else{
                    continue;
                }
            }
            else if(sortpatches[i].key == ESortKey::ENROLL_YEAR){
                if(a.get_enrolledStudent() != b.get_enrolledStudent()){
                    if(sortpatches[i].ascending){
                        return a.get_enrolledStudent() < b.get_enrolledStudent();
                    }else{
                        return a.get_enrolledStudent() > b.get_enrolledStudent();
                    }
                }else{
                    continue;
                }
            }
        }
        return a.get_StudentNumber() < b.get_StudentNumber();
    }

private:
    std::vector<Sortpatch> sortpatches;
};



class CompareStudents {
public:
    bool operator()(const std::shared_ptr<CStudent>& lhs, const std::shared_ptr<CStudent>& rhs) const {

        if (!lhs || !rhs) {
            return false;
        }
        if (lhs->get_BirthdayStudent() != rhs->get_BirthdayStudent()) {
            return lhs->get_BirthdayStudent() < rhs->get_BirthdayStudent();
        }
        if (lhs->get_enrolledStudent() != rhs->get_enrolledStudent()) {
            return lhs->get_enrolledStudent() < rhs->get_enrolledStudent();
        }

        return lhs->get_NameStudent() < rhs->get_NameStudent();
    }
};

class CompareStudents2 {
public:
    bool operator()(const std::shared_ptr<CStudent>& lhs, const std::shared_ptr<CStudent>& rhs) const {

        if (!lhs || !rhs) {
            return false;
        }
        if ( lhs->get_enrolledStudent() != rhs->get_enrolledStudent()) {
            return lhs->get_enrolledStudent() < rhs->get_enrolledStudent();
        }

        if (lhs->get_BirthdayStudent() != rhs->get_BirthdayStudent()) {
            return lhs->get_BirthdayStudent() < rhs->get_BirthdayStudent();
        }

        return lhs->get_NameStudent() < rhs->get_NameStudent();

    }
};
class CStudyDept
{
public:
    CStudyDept                    ()=default;
    bool                     addStudent                    ( const CStudent  & x );
    bool                     delStudent                    ( const CStudent  & x );
    std::list<CStudent>      search                        ( const CFilter   & flt,
                                                             const CSort     & sortOpt ) const;
    std::set<std::string>    suggest                       ( const std::string & name ) const;


private:

    std::set<std::shared_ptr<CStudent>, CompareStudents> m_StudentsSetBirth;
    std::set<std::shared_ptr<CStudent>, CompareStudents2> m_StudentsSetEnroll;
    int m_StudentsNumber=0;
};

std::set<std::string> CStudyDept::suggest(const std::string &name) const {

    std::set<std::string> tmp;

    std::stringstream ss(name);
    std::string word;
    while (ss >> word) {
        tmp.insert(Gulas(word));
    }

    std::set<std::string> result;

    for(auto & student : m_StudentsSetBirth){
        bool contains=true;
        for(auto & slovo : tmp ){
            if(!student->get_set().contains(slovo)){
                contains = false;
            }

        }
        if(contains){
            result.insert(student->get_NameStudent());
        }
    }
    return result;
}


std::list<CStudent> CStudyDept::search(const CFilter &flt, const CSort &sortOpt) const {

    if(m_StudentsSetBirth.empty() || m_StudentsSetEnroll.empty() ){
        std::list<CStudent> a;
        return a;
    }

    if(!flt.spravny_filter()){
        std::list<CStudent> a;
        return a;
    }

    std::list<CStudent> result;


    if(flt.empty_filter()){
        for(auto &a : m_StudentsSetEnroll){
            result.push_back(*a);
        }

    } else if(flt.getBB() == CDate(INT32_MAX,INT32_MAX,INT32_MAX) && flt.getBA() == CDate(INT32_MIN,INT32_MIN,INT32_MIN)){
        auto itlow = m_StudentsSetEnroll.upper_bound(std::make_shared<CStudent>("", CDate(INT32_MAX,INT32_MAX,INT32_MAX), flt.getEA()));
        auto itHigh = m_StudentsSetEnroll.upper_bound(std::make_shared<CStudent>("",CDate(INT32_MIN,INT32_MIN,INT32_MIN), flt.getEB()));


        for(auto it = itlow; it!=itHigh;++it){
            if(flt.getNames().empty()){
                result.push_back(*(*it));
            }
            else{

                    if(flt.getNames().contains((*it)->get_Gulas())){
                        result.push_back(*(*it));
                    }

            }
        }

    } else{
        auto itLow = m_StudentsSetBirth.upper_bound(std::make_shared<CStudent>("", flt.getBA(), INT32_MAX));
        auto itHigh = m_StudentsSetBirth.upper_bound(std::make_shared<CStudent>("",flt.getBB(), INT32_MIN));

        for(auto it = itLow;it!=itHigh;++it){
            if((*it)->get_enrolledStudent() < flt.getEB() && (*it)->get_enrolledStudent()>flt.getEA()){

                    if(flt.getNames().contains((*it)->get_Gulas())){
                        result.push_back(*(*it));
                    }

            }
        }


    }

    //sorting

    if(sortOpt.EmptySort()){

        result.sort([](const CStudent& a, const CStudent& b) {
            return a.get_StudentNumber() < b.get_StudentNumber();
        });
    }
    else{
        result.sort(sortOpt);
    }

    return result;


}

bool CStudyDept::addStudent(const CStudent &x) {

    std::shared_ptr<CStudent> tmp = std::make_shared<CStudent>(x);

    auto result = m_StudentsSetBirth.insert(tmp);

    if(result.second){
        tmp->set_Number(m_StudentsNumber);
        m_StudentsNumber++;

        auto  result2 = m_StudentsSetEnroll.insert(tmp);
        if(result2.second){
            return true;
        }
        return false;
    }else{
        return false;
    }
}


bool CStudyDept::delStudent(const CStudent &x) {
    std::shared_ptr<CStudent> tmp = std::make_shared<CStudent>(x.get_NameStudent(), x.get_BirthdayStudent(), x.get_enrolledStudent());


    auto it = m_StudentsSetBirth.find(tmp);


    if (it != m_StudentsSetBirth.end()) {
        m_StudentsSetBirth.erase(it);

        auto it2 = m_StudentsSetEnroll.find(tmp);
        if(it2!=m_StudentsSetEnroll.end()){
            m_StudentsSetEnroll.erase(it2);
            return true;
        }

        return false;
    }
    return false;

}

#ifndef __PROGTEST__
int main ( void )
{
    CStudyDept x0;
    assert ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) == CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) );
    assert ( ! ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) != CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) ) );
    assert ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) != CStudent ( "Peter Peterson", CDate ( 1980, 4, 11), 2010 ) );
    assert ( ! ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) == CStudent ( "Peter Peterson", CDate ( 1980, 4, 11), 2010 ) ) );
    assert ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) != CStudent ( "James Bond", CDate ( 1997, 6, 17), 2010 ) );
    assert ( ! ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) == CStudent ( "James Bond", CDate ( 1997, 6, 17), 2010 ) ) );
    assert ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) != CStudent ( "James Bond", CDate ( 1980, 4, 11), 2016 ) );
    assert ( ! ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) == CStudent ( "James Bond", CDate ( 1980, 4, 11), 2016 ) ) );
    assert ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) != CStudent ( "Peter Peterson", CDate ( 1980, 4, 11), 2016 ) );
    assert ( ! ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) == CStudent ( "Peter Peterson", CDate ( 1980, 4, 11), 2016 ) ) );
    assert ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) != CStudent ( "Peter Peterson", CDate ( 1997, 6, 17), 2010 ) );
    assert ( ! ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) == CStudent ( "Peter Peterson", CDate ( 1997, 6, 17), 2010 ) ) );
    assert ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) != CStudent ( "James Bond", CDate ( 1997, 6, 17), 2016 ) );
    assert ( ! ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) == CStudent ( "James Bond", CDate ( 1997, 6, 17), 2016 ) ) );
    assert ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) != CStudent ( "Peter Peterson", CDate ( 1997, 6, 17), 2016 ) );
    assert ( ! ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) == CStudent ( "Peter Peterson", CDate ( 1997, 6, 17), 2016 ) ) );
    assert ( x0 . addStudent ( CStudent ( "John Peter Taylor", CDate ( 1983, 7, 13), 2014 ) ) );
    assert ( x0 . addStudent ( CStudent ( "John Taylor", CDate ( 1981, 6, 30), 2012 ) ) );
    assert ( x0 . addStudent ( CStudent ( "Peter Taylor", CDate ( 1982, 2, 23), 2011 ) ) );
    assert ( x0 . addStudent ( CStudent ( "Peter John Taylor", CDate ( 1984, 1, 17), 2017 ) ) );
    assert ( x0 . addStudent ( CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ) ) );
    assert ( x0 . addStudent ( CStudent ( "James Bond", CDate ( 1982, 7, 16), 2013 ) ) );
    assert ( x0 . addStudent ( CStudent ( "James Bond", CDate ( 1981, 8, 16), 2013 ) ) );
    assert ( x0 . addStudent ( CStudent ( "James Bond", CDate ( 1981, 7, 17), 2013 ) ) );
    assert ( x0 . addStudent ( CStudent ( "James Bond", CDate ( 1981, 7, 16), 2012 ) ) );
    assert ( x0 . addStudent ( CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 ) ) );


    assert ( x0 . search ( CFilter (), CSort () ) == (std::list<CStudent>
            {
                    CStudent ( "John Peter Taylor", CDate ( 1983, 7, 13), 2014 ),
                    CStudent ( "John Taylor", CDate ( 1981, 6, 30), 2012 ),
                    CStudent ( "Peter Taylor", CDate ( 1982, 2, 23), 2011 ),
                    CStudent ( "Peter John Taylor", CDate ( 1984, 1, 17), 2017 ),
                    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ),
                    CStudent ( "James Bond", CDate ( 1982, 7, 16), 2013 ),
                    CStudent ( "James Bond", CDate ( 1981, 8, 16), 2013 ),
                    CStudent ( "James Bond", CDate ( 1981, 7, 17), 2013 ),
                    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2012 ),
                    CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 )
            }) );
    /*   std::list<CStudent> abema = x0 .  search ( CFilter (), CSort ());
       for(auto &a : abema){
           std::cout<<a<<std::endl;
       }
       std::cout<<std::endl<<std::endl;
       abema = x0 . search ( CFilter (), CSort () . addKey ( ESortKey::NAME, true ));
       for(auto &a : abema){
           std::cout<<a<<std::endl;
       }*/
    assert ( x0 . search ( CFilter (), CSort () . addKey ( ESortKey::NAME, true ) ) == (std::list<CStudent>
            {
                    CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 ),
                    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ),
                    CStudent ( "James Bond", CDate ( 1982, 7, 16), 2013 ),
                    CStudent ( "James Bond", CDate ( 1981, 8, 16), 2013 ),
                    CStudent ( "James Bond", CDate ( 1981, 7, 17), 2013 ),
                    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2012 ),
                    CStudent ( "John Peter Taylor", CDate ( 1983, 7, 13), 2014 ),
                    CStudent ( "John Taylor", CDate ( 1981, 6, 30), 2012 ),
                    CStudent ( "Peter John Taylor", CDate ( 1984, 1, 17), 2017 ),
                    CStudent ( "Peter Taylor", CDate ( 1982, 2, 23), 2011 )
            }) );
    assert ( x0 . search ( CFilter (), CSort () . addKey ( ESortKey::NAME, false ) ) == (std::list<CStudent>
            {
                    CStudent ( "Peter Taylor", CDate ( 1982, 2, 23), 2011 ),
                    CStudent ( "Peter John Taylor", CDate ( 1984, 1, 17), 2017 ),
                    CStudent ( "John Taylor", CDate ( 1981, 6, 30), 2012 ),
                    CStudent ( "John Peter Taylor", CDate ( 1983, 7, 13), 2014 ),
                    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ),
                    CStudent ( "James Bond", CDate ( 1982, 7, 16), 2013 ),
                    CStudent ( "James Bond", CDate ( 1981, 8, 16), 2013 ),
                    CStudent ( "James Bond", CDate ( 1981, 7, 17), 2013 ),
                    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2012 ),
                    CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 )
            }) );
    assert ( x0 . search ( CFilter (), CSort () . addKey ( ESortKey::ENROLL_YEAR, false ) . addKey ( ESortKey::BIRTH_DATE, false ) . addKey ( ESortKey::NAME, true ) ) == (std::list<CStudent>
            {
                    CStudent ( "Peter John Taylor", CDate ( 1984, 1, 17), 2017 ),
                    CStudent ( "John Peter Taylor", CDate ( 1983, 7, 13), 2014 ),
                    CStudent ( "James Bond", CDate ( 1982, 7, 16), 2013 ),
                    CStudent ( "James Bond", CDate ( 1981, 8, 16), 2013 ),
                    CStudent ( "James Bond", CDate ( 1981, 7, 17), 2013 ),
                    CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 ),
                    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ),
                    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2012 ),
                    CStudent ( "John Taylor", CDate ( 1981, 6, 30), 2012 ),
                    CStudent ( "Peter Taylor", CDate ( 1982, 2, 23), 2011 )
            }) );

    assert ( x0 . search ( CFilter () . name ( "james bond" ), CSort () . addKey ( ESortKey::ENROLL_YEAR, false ) . addKey ( ESortKey::BIRTH_DATE, false ) . addKey ( ESortKey::NAME, true ) ) == (std::list<CStudent>
            {
                    CStudent ( "James Bond", CDate ( 1982, 7, 16), 2013 ),
                    CStudent ( "James Bond", CDate ( 1981, 8, 16), 2013 ),
                    CStudent ( "James Bond", CDate ( 1981, 7, 17), 2013 ),
                    CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 ),
                    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ),
                    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2012 )
            }) );
    assert ( x0 . search ( CFilter () . bornAfter ( CDate ( 1980, 4, 11) ) . bornBefore ( CDate ( 1983, 7, 13) ) . name ( "John Taylor" ) . name ( "james BOND" ), CSort () . addKey ( ESortKey::ENROLL_YEAR, false ) . addKey ( ESortKey::BIRTH_DATE, false ) . addKey ( ESortKey::NAME, true ) ) == (std::list<CStudent>
            {
                    CStudent ( "James Bond", CDate ( 1982, 7, 16), 2013 ),
                    CStudent ( "James Bond", CDate ( 1981, 8, 16), 2013 ),
                    CStudent ( "James Bond", CDate ( 1981, 7, 17), 2013 ),
                    CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 ),
                    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ),
                    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2012 ),
                    CStudent ( "John Taylor", CDate ( 1981, 6, 30), 2012 )
            }) );
    assert ( x0 . search ( CFilter () . name ( "james" ), CSort () . addKey ( ESortKey::NAME, true ) ) == (std::list<CStudent>
            {
            }) );
    assert ( x0 . suggest ( "peter" ) == (std::set<std::string>
            {
                    "John Peter Taylor",
                    "Peter John Taylor",
                    "Peter Taylor"
            }) );
    assert ( x0 . suggest ( "bond" ) == (std::set<std::string>
            {
                    "Bond James",
                    "James Bond"
            }) );
    /*  std::set<std::string> a =  x0 . suggest ( "peter joHn" );
      for(auto & b : a){
          std::cout<<b<<std::endl;
      }*/

    assert ( x0 . suggest ( "peter joHn" ) == (std::set<std::string>
            {
                    "John Peter Taylor",
                    "Peter John Taylor"
            }) );
    assert ( x0 . suggest ( "peter joHn bond" ) == (std::set<std::string>
            {
            }) );
    assert ( x0 . suggest ( "pete" ) == (std::set<std::string>
            {
            }) );
    assert ( x0 . suggest ( "peter joHn PETER" ) == (std::set<std::string>
            {
                    "John Peter Taylor",
                    "Peter John Taylor"
            }) );
    assert ( ! x0 . addStudent ( CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ) ) );
    assert ( x0 . delStudent ( CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ) ) );
    assert ( x0 . search ( CFilter () . bornAfter ( CDate ( 1980, 4, 11) ) . bornBefore ( CDate ( 1983, 7, 13) ) . name ( "John Taylor" ) . name ( "james BOND" ), CSort () . addKey ( ESortKey::ENROLL_YEAR, false ) . addKey ( ESortKey::BIRTH_DATE, false ) . addKey ( ESortKey::NAME, true ) ) == (std::list<CStudent>
            {
                    CStudent ( "James Bond", CDate ( 1982, 7, 16), 2013 ),
                    CStudent ( "James Bond", CDate ( 1981, 8, 16), 2013 ),
                    CStudent ( "James Bond", CDate ( 1981, 7, 17), 2013 ),
                    CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 ),
                    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2012 ),
                    CStudent ( "John Taylor", CDate ( 1981, 6, 30), 2012 )
            }) );
    assert ( ! x0 . delStudent ( CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ) ) );
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
