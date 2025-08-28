// -*- mode:C++; c-basic-offset:2; indent-tabs-mode:nil -*-
/*
Copyright © 2015 Glen S. Dayton

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the “Software”), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
/**
  *  Extra light framework for unit testing in C++.
  *
  *  Typical use is to define your tests as in the following example:
  *
  *  #include <CppUnitXLite/CppUnitXLite.cpp>
  *
  *  TEST(test_classname, test_name)
  *  {
  *     CHECK(condition);
  *     CHECK_EQUAL(expected, actual);
  *     if (condition) FAIL("Arbitrary error message”);
  *  }
  *
  *  TESTMAIN
  *
  *  Liberally adapted from Michael Feather's CppUnitLite (downloaded from
  *  http://www.objectmentor.com/resources/bin/CppUnitLite.zip)
  *
  *  Some of the changes from CppUnitLite include the following:
  *     *  Reversed order of arguments of TEST macro to match other frameworks
  *        such as googletest and unittest.
  *     *  Use C++ templates to reduce the need for lots of CHECK macros.
  *
  *   CHECK_EQUAL should work with any data type that has an operator==().
  *   CHECK_EQUAL instantiates to a templated method, which does have an
  *   explicit instantiation for comparing const char * style strings.
  */

#ifndef CPP_UNIT_X_LITE_H_
#define CPP_UNIT_X_LITE_H_

#include <iostream>
#include <sstream>
#include <string>
#include <utility>

struct Failure;

class Test;

class TestRegistry;

class TestResult;


#define TEST(testGroup, testName)\
class testGroup##testName##Test : public Test \
{ public: testGroup##testName##Test () : Test (#testName "Test") {} \
  void run (TestResult& theResult); } \
testGroup##testName##Instance; \
void testGroup##testName##Test::run (TestResult& theResult)

#define CHECK(condition) check(theResult, (condition), #condition, __FILE__, __LINE__)

#define CHECK_EQUAL(expected, actual) checkEqual((expected), (actual), theResult, __FILE__, __LINE__)
#define CHECK_LE(expected, actual) checkLE((expected), (actual), theResult, __FILE__, __LINE__)
#define CHECK_LT(expected, actual) checkLT((expected), (actual), theResult, __FILE__, __LINE__)
#define CHECK_GT(expected, actual) checkGT((expected), (actual), theResult, __FILE__, __LINE__)
#define CHECK_GE(expected, actual) checkGE((expected), (actual), theResult, __FILE__, __LINE__)

#define CHECK_APPROX_EQUAL(expected, actual, threshold) checkApproxEqual((expected), (actual), (threshold), theResult, __FILE__, __LINE__)

#define FAIL(text) fail(theResult, (text), __FILE__, __LINE__)

#define TESTMAIN int main(int, char **) { TestResult tr; TestRegistry::runAll(tr); return 0; }


/**
 * Constructor of Test registers the test instance with the
 * TestRegistry during the static initialization phase.
 */
class TestRegistry {
public:
    TestRegistry() : tests(nullptr) {}
    static void addTest(Test *test) { instance().add(test); }

    static void runAll(TestResult &result) { instance().run(result); }

private:
    static TestRegistry &instance() {
        static TestRegistry registry;
        return registry;
    }

    void add(Test *test);

    void run(TestResult &result);

    Test *tests;
};


/**
 *  Inherit from Test to define your own unit test.
 */
class Test {
public:
    explicit Test(const char *theTestName);

    virtual ~Test() = default;

    /**
     * Override the run() method to execute your own tests.
     *
     * @param result Pass the result argument to the check methods
     *               to record results.
     */
    virtual void run(TestResult &result) = 0;

    inline void next(Test *test) { nextTest = test; }

    [[nodiscard]] inline Test *next() const { return nextTest; }

protected:
    auto check(TestResult &result,
               bool condition,
               const char *conditionString,
               const char *fileName = __FILE__,
               unsigned int lineNumber = __LINE__) -> bool {
        if (!condition) { fail(result, conditionString, fileName, lineNumber); }
        return condition;
    }


    auto fail(TestResult &result,
              const char *conditionString,
              const char *fileName = __FILE__,
              unsigned int lineNumber = __LINE__) -> bool;

    template<typename SubjectType>
    auto checkEqual(SubjectType expected,
                    SubjectType actual,
                    TestResult &result,
                    const char *fileName = __FILE__,
                    unsigned int lineNumber = __LINE__) -> bool {
        bool successful = expected == actual;
        if (!successful) {
            std::ostringstream message;
            message << "expected: " << expected << " but received: " << actual;
            fail(result, message.str().c_str(), fileName, lineNumber);
        }
        return successful;
    }

    template<typename SubjectType>
    auto checkLE(SubjectType expected,
                 SubjectType actual,
                 TestResult &result,
                 const char *fileName = __FILE__,
                 unsigned int lineNumber = __LINE__) -> bool {
        bool successful = expected <= actual;
        if (!successful) {
            std::ostringstream message;
            message << "expected " << expected << " not <= actual " << actual;
            fail(result, message.str().c_str(), fileName, lineNumber);
        }
        return successful;
    }

    template<typename SubjectType>
    auto checkLT(SubjectType expected,
                 SubjectType actual,
                 TestResult &result,
                 const char *fileName = __FILE__,
                 unsigned int lineNumber = __LINE__) -> bool {
        bool successful = expected < actual;
        if (!successful) {
            std::ostringstream message;
            message << "expected " << expected << " not < actual " << actual;
            fail(result, message.str().c_str(), fileName, lineNumber);
        }
        return successful;
    }

    template<typename SubjectType>
    auto checkGT(SubjectType expected,
                 SubjectType actual,
                 TestResult &result,
                 const char *fileName = __FILE__,
                 unsigned int lineNumber = __LINE__) -> bool {
        bool successful = expected > actual;
        if (!successful) {
            std::ostringstream message;
            message << "expected " << expected << " not > actual " << actual;
            fail(result, message.str().c_str(), fileName, lineNumber);
        }
        return successful;
    }

    template<typename SubjectType>
    auto checkGE(SubjectType expected,
                 SubjectType actual,
                 TestResult &result,
                 const char *fileName = __FILE__,
                 unsigned int lineNumber = __LINE__) -> bool {
        bool successful = expected >= actual;
        if (!successful) {
            std::ostringstream message;
            message << "expected " << expected << " not >= actual " << actual;
            fail(result, message.str().c_str(), fileName, lineNumber);
        }
        return successful;
    }

    template<typename SubjectType>
    auto checkApproxEqual(SubjectType expected,
                          SubjectType actual,
                          SubjectType threshold,
                          TestResult &result,
                          const char *fileName = __FILE__,
                          unsigned int lineNumber = __LINE__) -> bool;

private:
    template<typename SubjectType>
    static SubjectType abs(SubjectType x) { return x < 0 ? -x : x; }

    std::string testName;
    Test *nextTest;
};


/**
 *  Record everything knowable about the circumstance and
 *  location of a failure.
 */
struct Failure {
    Failure(std::string theTestName,
            std::string theFileName,
            unsigned int theLineNumber,
            std::string theCondition)
            : message(std::move(theCondition)),
              testName(std::move(theTestName)),
              fileName(std::move(theFileName)),
              lineNumber(theLineNumber) {}

    std::string message;
    std::string testName;
    std::string fileName;
    unsigned int lineNumber;
};


/**
 *  Collect all of the results of tests and checks.
 */
class TestResult {
public:
    TestResult() : failureCount(0) {}

    virtual ~TestResult() = default;

    virtual void addFailure(const Failure &failure) {
        std::cout << failure.fileName << ":" << failure.lineNumber << ":0 test \"" << failure.message << "\" failed"
                  << std::endl;
        addFailureCount();
    }

    virtual void testsEnded() {
        if (failureCount > 0) {
            std::cout << "There were " << failureCount << " failures" << std::endl;
        } else {
            std::cout << "There were no test failures" << std::endl;
        }
    }

protected:
    auto addFailureCount(int increment = 1) -> int {
        failureCount += increment;
        return failureCount;
    }

private:
    int failureCount;
};


inline auto
Test::fail(TestResult &result,
           const char *conditionString,
           const char *fileName,
           unsigned int lineNumber) -> bool {
    result.addFailure(Failure(testName, fileName, lineNumber, conditionString));
    return false;
}


template<typename SubjectType>
auto Test::checkApproxEqual(SubjectType expected,
                       SubjectType actual,
                       SubjectType threshold,
                       TestResult &result,
                       const char *fileName,
                       unsigned int lineNumber) -> bool {
    bool successful = abs(expected - actual) <= threshold;
    if (!successful) {
        std::ostringstream message;
        message << "expected: " << expected << " but received: " << actual;
        fail(result, message.str().c_str(), fileName, lineNumber);
    }
    return successful;
}

#endif // CPP_UNIT_X_LITE_H_
