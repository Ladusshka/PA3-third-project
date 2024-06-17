# PA3-third-project
The challenge is to implement classes that implement student management in the study department.
We assume that the student affairs department is in charge of the students' agenda. For simplicity, each student is represented by his/her name (we consider one string for surname and first name or multiple names, each word separated by at least one space), date of birth and year of entry to the faculty. We want to be able to add, remove, and search the student database. About students, we assume that the data triplet of name + date of birth + year of entry is unique, not repeated in the database. Of course, the names, dates of birth, and years of entry themselves may already be repeated. When adding and removing a student, we always enter an already filled student instance (containing the mentioned triple of data).

The search is a bit more complicated. When searching, we want to filter students by name, date of birth and year of entry to the faculty. The returned result is a list of students, and we want to be able to sort this list according to the given criteria (name, date of birth, year of entry to the faculty, order of registration).
Searching is a bit more complicated. When searching, we want to filter students by name, date of birth and year of entry to the faculty. The returned result is a list of students, and we want to be able to sort this list by the specified criteria (name, date of birth, year of entry, order of registration).

The last method of the interface will be the whisperer, a method that for a given part of a student's name selects all students that match the given pattern.
The whole implementation is divided into several classes. In the attached source code you can find the basis of the solution - the implementation of some classes and the required interface of the remaining classes. Their description follows:
The CDate class represents a simple date. Instances of this class will be used to store the students' date of birth and to filter by date of birth. The class is implemented in the test environment and is also embedded (in the conditional translation block) in the attached source file. The meaning of the methods is as follows:

Constructor (y,m,d)
    initializes the instance with the specified year, month and day.
operator <=> (date)
    method compares this and the date instance. The result of the method is one of the std::strong_ordering values.
output operator <<
    displays the date in the specified stream, the function is mainly used for testing and debugging statements.
Note:
    The class is implemented in the test environment, the implementation provided in the attached file is only for your debugging purposes and will not apply when testing on Progtest. Thus, there is no point in trying to add additional methods to the interface, they will      not be available after you submit to Progtest.
    The ESortKey enumeration type is used to identify the sort criteria. The enumeration type is declared in the test environment, the supplied implementation is located in the conditional compilation block and is only used for local testing. It has the following allowed      values:

NAME
    sorting by student name,
BIRTH_DATE
    sort by student's date of birth,
ENROLL_YEAR
    sort by year of entry to the faculty.
Note
    This is a C++11 enumeration type where the compiler strictly insists that the type of the variable and the type of the value being assigned match. Values must be handled using a fully qualified name, such as ESortKey::NAME.
    The CStudent class represents a single student in the database. Its implementation is up to you. The mandatory public interface is:

constructor(name, dateOfBirth, enrollYear)
    The constructor initializes the instance using the given parameters.
operator ==
    compares two instances of CStudent. It will consider them to be identical if they are exactly the same in name, date of birth, and enrollment year. Name comparison is case sensitive and distinguishes the order of names (e.g., "Jan Jakub Ryba" and "Jakub Jan Ryba"        are not the same name).
operator !=
    compares two instances of CStudent. It will consider them to be different if they differ exactly in name, date of birth, or year of entry to the faculty (thus, according to convention, this is a negation of the result of the == operator).
next
Your implementation can supply the class with additional methods and member variables that you need.


The CFilter class represents criteria for filtering students in a search:
constructor
    the constructor initializes an empty filter (any record will satisfy such a filter),
bornBefore
    adds a restriction to the filter that only students born before the specified date will comply with (students born on the specified day will no longer comply with the filter),
bornAfter
    adds a restriction to the filter that only students born after the specified date will comply with (students born on the specified day will no longer comply with the filter),
enrolledBefore
    adds a restriction to the filter that only students enrolled before the specified year will comply with (students enrolled in the specified year will no longer comply with the filter),
enrolledAfter
    adds a restriction to the filter that will be met only by students enrolled after the specified year (students enrolled in the specified year will no longer meet the filter),    
Name
adds a restriction on the name (or multiple names) of students to the filter. The behavior is slightly different from the other criteria:
if the name method was not used in the filter, the filter does not limit the result by student names,
if the name method is called exactly once, the student names must match the specified string,
if the name method is called multiple times, the student names must match some specified string.
Filtering by name(s) also has a more complicated comparison of its own: when filtering, we compare names without distinguishing between uppercase and lowercase letters, and further, when comparing, we consider names that differ in word order to be the same. So, for example, we consider "Jan Jakub Ryba" and "Jakub Jan Ryba" and "RYBA jan JaKuB" to be the same in comparison (but, for example, "Jan Jakub Jan Ryba" is already different).
next
Your implementation can supply the class with additional methods and member variables that you need.    


The CSort class represents the criteria for sorting students in the search result. Sorting can use multiple criteria for comparison, each criterion can be ascending or descending. Suppose we have the sorting set to sort by name (first criterion) and by date of birth (second criterion). Thus, when comparing students, first the names are compared, if they differ, the order of the compared students is given. If the names do not differ, the date of birth is used for comparison. Again, if the dates of birth differ, the order is given, otherwise any additional sorting criterion is used. If no other sorting criterion is available during sorting and the order is still undecided, the order of the student's registration in the database is used (stable sorting). Note that if we do not set any sort criteria, the search result should be in order of student registration.

constructor
constructor initializes an empty list of sort criteria,
addKey (key, ascending)
    method will add another sort criterion. The criterion is given by the value of the ESortKey enumeration type (first parameter), the second parameter is the value true for ascending sorting according to the specified criterion or false for descending sorting       according to the specified criterion.
next
    Your implementation can supply the class with additional methods and member variables that you need.


The CStudyDept class represents the student database. The database provides the following interface:
constructor
constructor initializes an empty database,
addStudent (student)
    the method adds the student to the database, returns a signal of success (true) or failure (false - duplicate student),
delStudent (student)
    the method removes the student from the database, returns a signal of success (true) or failure (false - the student did not exist in the database),
search (filter, sortOpt)
    the method searches the database for students who meet the criteria of the filter filter and returns their list sorted in the order given by the conditions in sortOpt,
suggest (name)
    method serves as a whisperer for the database user interface. The method takes the string name, splits it into individual words, and finds registered students such that their name contains all words from name thus obtained. Word matching is case insensitive (case        insensitive). For example, if the students "Jan Jakub Ryba", "Jan Ryba" and "Jan Novak" are registered in the database, then the call suggest("jan") will include all three of these names, the call suggest("Ryba JaN") will return only the first two of of them,            calling suggest("Fish Jakub") returns only the first of them, suggest("Fish Me") returns an empty set, and suggest("Jan jan JAN Fish RyBa") returns the first two names.
next
    Your implementation can supply the class with additional methods and member variables that you need.
