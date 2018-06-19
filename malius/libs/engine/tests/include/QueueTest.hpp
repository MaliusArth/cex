#pragma once

// external libraries
#include <gtest/gtest.h>

#include <malius/core/lang.hpp>

// tested libraries
#include <malius/sample_class_lib-inl.hpp>

// To use a test fixture, derive a class from testing::Test.
class QueueTest : public testing::Test {
protected:  // You should make the members protected s.t. they can be
    // accessed from sub-classes.

    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the varaibles.
    // Otherwise, this can be skipped.
    virtual void SetUp()  MA_OVERRIDE
    {
        q1_.Enqueue(1);
        q2_.Enqueue(2);
        q2_.Enqueue(3);
    }

    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    //
    // virtual void TearDown() {
    // }

    // A helper function that some test uses.
    static int Double(int n) {
        return 2 * n;
    }

    // A helper function for testing Queue::Map().
    void MapTester(const Queue<int> * q) const
    {
        // Creates a new queue, where each element is twice as big as the
        // corresponding one in q.
        const Queue<int> * const new_q = q->Map(Double);

        // Verifies that the new queue has the same size as q.
        ASSERT_EQ(q->Size(), new_q->Size());

        // Verifies the relationship between the elements of the two queues.
        for (const QueueNode<int> * n1 = q->Head(), *n2 = new_q->Head();
            n1 != nullptr; n1 = n1->next(), n2 = n2->next()) {
            EXPECT_EQ(2 * n1->element(), n2->element());
        }

        delete new_q;
    }

    // Declares the variables your tests want to use.
    Queue<int> q0_;
    Queue<int> q1_;
    Queue<int> q2_;
};
