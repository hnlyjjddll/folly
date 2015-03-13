/*
 * Copyright 2015 Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>

#include <folly/futures/Future.h>

using namespace folly;

TEST(Sugar, pollReady) {
  Promise<int> p;
  auto f = p.getFuture();
  p.setValue(42);
  EXPECT_EQ(42, f.poll().value().value());
}

TEST(SUGAR, pollNotReady) {
  Promise<int> p;
  auto f = p.getFuture();
  EXPECT_FALSE(f.poll().hasValue());
}

TEST(SUGAR, pollException) {
  Promise<void> p;
  auto f = p.getFuture();
  p.fulfil([] { throw std::runtime_error("Runtime"); });
  EXPECT_TRUE(f.poll().value().hasException());
}
