/**
 * @file OperationManagerTests.cpp
 *
 * @brief  This class is used for unit testing the OperationManager using GTest.
 *
 * @ingroup Testing
 *
 * These tests don't act independently since the OperationManager is a singleton. Each change to the state of
 * OperationManager will be carried through onto other tests.
 */

#include "gtest/gtest.h"

#include "Foo.h"
#include "Core/OperationManager.h"
#include "Core/Operations.h"

TEST(OperationManager, GetInstanceReturnsInstance) {
    OperationManager *operationManager = &OperationManager::getInstance();
    ASSERT_TRUE(operationManager != nullptr);
}

TEST(OperationManager, AddingOneOperation) {
    Foo foo;
    function<void()> function = std::bind(&Foo::deallocateMemory, foo);
    EXPECT_NO_FATAL_FAILURE(OperationManager::getInstance().registerOperation(Operations::op::deallocateMemory, function));
}

TEST(OperationManager, AddingManyOperations) {
    Foo foo;
    function<void()> function = std::bind(&Foo::deallocateMemory, foo);
    for (int i = 0; i < 10000; i++) {
        EXPECT_NO_FATAL_FAILURE(OperationManager::getInstance().registerOperation(Operations::op::deallocateMemory, function));
    }
}

TEST(OperationManager, OperationExecutionSuccess) {
    EXPECT_NO_FATAL_FAILURE(OperationManager::getInstance().executeOperation(Operations::op::deallocateMemory));
}

TEST(OperationManager, OperationExecutionContainsNoFunctionsOfOperationType) {
    EXPECT_NO_FATAL_FAILURE(OperationManager::getInstance().executeOperation(Operations::copyToGPU));
}