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
  *  Test CppUnitXLite without using the convenience macros.
  */
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "CppUnitXLite.hpp"
#include "CppUnitXLiteTests.hpp"

unsigned int expectedFailures = 0;

// Alternate representation of the same tests expressed without macros
//  To define a test do the following:
//  1.  Inherit from Test
//  2.  Define your test's constructor. Register the test and its name with
//      the Test() constructor
//  2.  Override the run(TestResult&) method
//  4.  Supply the TestResult argument to your check method invocations
//  5.  Define an instance variable so an instance of your class will get
//      constructued
namespace CppUnitXLiteTest
{
struct FailTest : public Test
{
  FailTest() : Test("CppUnitXLiteTest::FailTest") { }
  void run(TestResult &result)
  {
    fail(result, "Expected failure"); ++expectedFailures;
  }
} FailTestInstance;


struct CheckTest : public Test
{
  CheckTest() : Test("CppUnitXLiteTest::CheckTest") { }
  void run(TestResult &result)
  {
    check(result, false, "expected false"); ++expectedFailures;
    check(result, true, "expect no error");
  }
} CheckTestInstance;


// The macros use the argument "theResult" so even if you use the class method
//  of defining tests, you may mix macros
struct CheckEqualTest : public Test
{
  CheckEqualTest() : Test("CppUnitXLiteTest::CheckEqualTest"){}

  void run(TestResult &theResult)
  {
    std::string actual = "The rain in Spain";
    CHECK_EQUAL(std::string("The Rain in Spain"), actual); ++expectedFailures;
    CHECK_EQUAL(std::string("The rain in Spain"), actual);
  }
} CheckEqualTest;
}//namespace CppUnitXLiteTest
