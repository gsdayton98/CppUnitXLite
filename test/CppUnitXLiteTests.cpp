// -*- mode:C++; c-basic-offset:2; indent-tabs-mode:nil -*-
/*
Copyright (c) 2015 Glen S. Dayton

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
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
  *  Test CppUnitXLite
  */
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <CppUnitXLite/CppUnitXLite.hpp>
// Cheap way to get one-time linker definitions without mucking up the command line
#include <CppUnitXLite/CppUnitXLite.cpp>
#include "CppUnitXLiteTests.hpp"


unsigned int expectedFailures = 0;


InstrumentedResult::InstrumentedResult()
: TestResult(),
  collectedFailures()
{ }

void
InstrumentedResult::addFailure(const Failure &failure)
{
  collectedFailures.push_back(failure);
}

unsigned int
InstrumentedResult::numberFailures() const
{
  return collectedFailures.size();
}


std::vector<Failure>::const_iterator
InstrumentedResult::begin() const
{
  return collectedFailures.begin();
}

std::vector<Failure>::const_iterator
InstrumentedResult::end() const
{
  return collectedFailures.end();
}


TEST(CppUnitXLiteTest, Fail)
{
  FAIL("Expected failure"); ++expectedFailures;
}


TEST(CppUnitXLiteTest, Check)
{
  CHECK(false); ++expectedFailures;
  CHECK(true);
}


TEST(CppUnitXLiteTest, CheckEqual)
{
  std::string actual = "The rain in Spain";
  CHECK_EQUAL(std::string("The Rain in Spain"), actual); ++expectedFailures;
  CHECK_EQUAL(std::string("The rain in Spain"), actual);
}


TEST(CppUnitXLiteTest, CheckApproxEqual)
{
  CHECK_APPROX_EQUAL(4.0, sqrt(16.0), 1.0E-15);
  CHECK_APPROX_EQUAL(2.5, 3.0, 1.0);
  CHECK_APPROX_EQUAL(2.5, 3.0, 0.1);  ++expectedFailures;
}


TEST(CppUnitXLiteTest, CheckConstCharStar)
{
  static const char actual[] = "aardvark";
  CHECK_EQUAL("aardvark", actual);
  CHECK_EQUAL("giraffe", actual);  ++expectedFailures;
}

// Custom main() to drive tests of the test framework.
//  In normal circumstances just use the
//  TESTMAIN
//  macro

int
main(int, char **)
{
  int exitStatus = EXIT_FAILURE;

  try
  {
    InstrumentedResult tr;
    TestRegistry::runAll(tr);

    if (tr.numberFailures() != expectedFailures)
    {
      std::cerr << "Did not get expected failures" << std::endl;

      #if __cplusplus >= 201103L
      for (const auto &f : tr)
      {
        std::cout << f.testName << ": " << f.message << ": " << f.fileName << "@" << f.lineNumber << std::endl;
      }
      #else
      for (std::vector<Failure>::const_iterator f=tr.begin(); f != tr.end(); ++f)
      {
        std::cout << f->testName << ": " << f->message << ": " << f->fileName << "@" << f->lineNumber << std::endl;
      }
      #endif
    }

    exitStatus = EXIT_SUCCESS;
  }
  catch (const std::exception& ex)
  {
    std::cerr << "Unhandled exception: " << ex.what() << std::endl;
  }
  catch (...)
  {
    std::cerr << "Non standard exception" << std::endl;
  }
  return exitStatus;
}

