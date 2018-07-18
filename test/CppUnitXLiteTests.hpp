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
#ifndef CPPUNITXLITETEST_H
#define CPPUNITXLITETEST_H
#include <vector>
#include "CppUnitXLite.hpp"

// To test the test framework itself, overload the TestResult class to not
// indicate errors when we get an expected failure.
class InstrumentedResult : public TestResult
{
public:
  InstrumentedResult();
  virtual void addFailure(const Failure &failure);
  unsigned int numberFailures() const;

  std::vector<Failure>::const_iterator begin() const;
  std::vector<Failure>::const_iterator end() const;

private:
  std::vector<Failure> collectedFailures;
};


// Global count of the expected failures encountered so far
extern unsigned int expectedFailures;

#endif
