#include "CppUnitTest.h"
#include "../Library/Matrix.h"
#include "../Library/Exercise.h"
#include "../Library/OurEx1.h"
#include "../Library/OurEx2.h"
#include "../Library/OurEx3.h"
#include "../Library/RandomGenerator.h"
#include "../Library/ConstantGenerator.h"
#include "../Library/IStreamGenerator.h"
#include <sstream>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AlgebraTests
{
    TEST_CLASS(MatrixTests)
    {
    public:
        TEST_METHOD(MatrixConstructor_ValidSize_Success)
        {
            // Arrange & Act
            miit::algebra::Matrix<int> matrix(5);

            // Assert
            Assert::AreEqual(size_t(5), matrix.get_size());
        }

        TEST_METHOD(MatrixConstructor_ZeroSize_Success)
        {
            // Arrange & Act
            miit::algebra::Matrix<int> matrix(0);

            // Assert
            Assert::AreEqual(size_t(0), matrix.get_size());
        }

        TEST_METHOD(MatrixAccessOperator_ValidIndex_Success)
        {
            // Arrange
            miit::algebra::Matrix<int> matrix(3);
            matrix[0] = 1;
            matrix[1] = 2;
            matrix[2] = 3;

            // Act & Assert
            Assert::AreEqual(1, matrix[0]);
            Assert::AreEqual(2, matrix[1]);
            Assert::AreEqual(3, matrix[2]);
        }

        TEST_METHOD(MatrixAccessOperator_InvalidIndex_ThrowsException)
        {
            // Arrange
            miit::algebra::Matrix<int> matrix(3);

            // Act & Assert
            auto func = [&matrix] { return matrix[5]; };
            Assert::ExpectException<std::out_of_range>(func);
        }

        TEST_METHOD(MatrixCopyConstructor_Success)
        {
            // Arrange
            miit::algebra::Matrix<int> original(2);
            original[0] = 10;
            original[1] = 20;

            // Act
            miit::algebra::Matrix<int> copy(original);

            // Assert
            Assert::AreEqual(original.get_size(), copy.get_size());
            Assert::AreEqual(original[0], copy[0]);
            Assert::AreEqual(original[1], copy[1]);
        }

        TEST_METHOD(MatrixMoveConstructor_Success)
        {
            // Arrange
            miit::algebra::Matrix<int> original(2);
            original[0] = 10;
            original[1] = 20;

            // Act
            miit::algebra::Matrix<int> moved(std::move(original));

            // Assert
            Assert::AreEqual(size_t(2), moved.get_size());
            Assert::AreEqual(10, moved[0]);
            Assert::AreEqual(20, moved[1]);
            Assert::AreEqual(size_t(0), original.get_size());
        }

        TEST_METHOD(MatrixLeftShift_ValidShift_Success)
        {
            // Arrange
            miit::algebra::Matrix<int> matrix(4);
            matrix[0] = 1;
            matrix[1] = 2;
            matrix[2] = 3;
            matrix[3] = 4;

            // Act
            auto result = matrix << 1;

            // Assert
            Assert::AreEqual(2, result[0]);
            Assert::AreEqual(3, result[1]);
            Assert::AreEqual(4, result[2]);
            Assert::AreEqual(1, result[3]);
        }

        TEST_METHOD(MatrixRightShift_ValidShift_Success)
        {
            // Arrange
            miit::algebra::Matrix<int> matrix(4);
            matrix[0] = 1;
            matrix[1] = 2;
            matrix[2] = 3;
            matrix[3] = 4;

            // Act
            auto result = matrix >> 1;

            // Assert
            Assert::AreEqual(4, result[0]);
            Assert::AreEqual(1, result[1]);
            Assert::AreEqual(2, result[2]);
            Assert::AreEqual(3, result[3]);
        }

        TEST_METHOD(MatrixToString_ValidArray_ReturnsCorrectString)
        {
            // Arrange
            miit::algebra::Matrix<int> matrix(3);
            matrix[0] = 1;
            matrix[1] = 2;
            matrix[2] = 3;

            // Act
            std::string result = matrix.to_string();

            // Assert
            Assert::AreEqual(std::string("[1, 2, 3]"), result);
        }
    };

    TEST_CLASS(GeneratorTests)
    {
    public:
        TEST_METHOD(RandomGenerator_ValidRange_Success)
        {
            // Arrange
            miit::algebra::RandomGenerator generator(1, 10);

            // Act
            int value = generator.generate();

            // Assert
            Assert::IsTrue(value >= 1 && value <= 10);
        }

        TEST_METHOD(ConstantGenerator_AlwaysReturnsConstant_Success)
        {
            // Arrange
            miit::algebra::ConstantGenerator generator(42);

            // Act
            int value1 = generator.generate();
            int value2 = generator.generate();

            // Assert
            Assert::AreEqual(42, value1);
            Assert::AreEqual(42, value2);
        }

        TEST_METHOD(IStreamGenerator_ReadsFromStream_Success)
        {
            // Arrange
            std::stringstream ss("123 456");
            miit::algebra::IStreamGenerator generator(ss);

            // Act
            int value1 = generator.generate();
            int value2 = generator.generate();

            // Assert
            Assert::AreEqual(123, value1);
            Assert::AreEqual(456, value2);
        }
    };

    TEST_CLASS(ExerciseTests)
    {
    public:
        TEST_METHOD(ExerciseConstructor_ValidParameters_Success)
        {
            // Arrange
            auto generator = std::make_unique<miit::algebra::ConstantGenerator>(5);

            // Act
            miit::algebra::OurEx1 exercise(3, std::move(generator));

            // Assert
            Assert::AreEqual(size_t(3), exercise.get_matrix().get_size());
        }

        TEST_METHOD(ExerciseFillMatrix_Success)
        {
            // Arrange
            auto generator = std::make_unique<miit::algebra::ConstantGenerator>(7);
            miit::algebra::OurEx1 exercise(3, std::move(generator));

            // Act
            exercise.fill_matrix();

            // Assert
            Assert::AreEqual(7, exercise.get_matrix()[0]);
            Assert::AreEqual(7, exercise.get_matrix()[1]);
            Assert::AreEqual(7, exercise.get_matrix()[2]);
        }
    };

    TEST_CLASS(OurEx1Tests)
    {
    public:
        TEST_METHOD(OurEx1Task_ReplacesMinPositiveWithZero_Success)
        {
            // Arrange
            auto generator = std::make_unique<miit::algebra::ConstantGenerator>(0);
            miit::algebra::OurEx1 exercise(5, std::move(generator));

            // Manually set matrix values
            auto& matrix = const_cast<miit::algebra::Matrix<int>&>(exercise.get_matrix());
            matrix[0] = 5;
            matrix[1] = -3;
            matrix[2] = 2;  // minimal positive by modulus
            matrix[3] = 8;
            matrix[4] = -1;

            // Act
            exercise.Task();

            // Assert
            Assert::AreEqual(5, matrix[0]);
            Assert::AreEqual(-3, matrix[1]);
            Assert::AreEqual(0, matrix[2]);  // should be replaced with 0
            Assert::AreEqual(8, matrix[3]);
            Assert::AreEqual(-1, matrix[4]);
        }

        TEST_METHOD(OurEx1Task_NoPositiveElements_NoChanges)
        {
            // Arrange
            auto generator = std::make_unique<miit::algebra::ConstantGenerator>(0);
            miit::algebra::OurEx1 exercise(3, std::move(generator));

            // Manually set matrix values
            auto& matrix = const_cast<miit::algebra::Matrix<int>&>(exercise.get_matrix());
            matrix[0] = -5;
            matrix[1] = -3;
            matrix[2] = -1;

            // Act
            exercise.Task();

            // Assert
            Assert::AreEqual(-5, matrix[0]);
            Assert::AreEqual(-3, matrix[1]);
            Assert::AreEqual(-1, matrix[2]);
        }

        TEST_METHOD(OurEx1Task_EmptyArray_NoChanges)
        {
            // Arrange
            auto generator = std::make_unique<miit::algebra::ConstantGenerator>(0);
            miit::algebra::OurEx1 exercise(0, std::move(generator));

            // Act & Assert (should not throw)
            exercise.Task();
        }
    };

    TEST_CLASS(OurEx2Tests)
    {
    public:
        TEST_METHOD(OurEx2GetFirstDigit_ValidNumbers_Success)
        {
            // Arrange
            miit::algebra::OurEx2 exercise(0, std::make_unique<miit::algebra::ConstantGenerator>(0));

            // Act & Assert
            Assert::AreEqual(1, exercise.GetFirst_Digit(123));
            Assert::AreEqual(5, exercise.GetFirst_Digit(567));
            Assert::AreEqual(9, exercise.GetFirst_Digit(9));
            Assert::AreEqual(1, exercise.GetFirst_Digit(-123));  // should work with negative
        }

        TEST_METHOD(OurEx2GetLastDigit_ValidNumbers_Success)
        {
            // Arrange
            miit::algebra::OurEx2 exercise(0, std::make_unique<miit::algebra::ConstantGenerator>(0));

            // Act & Assert
            Assert::AreEqual(3, exercise.Get_LastDigit(123));
            Assert::AreEqual(7, exercise.Get_LastDigit(567));
            Assert::AreEqual(9, exercise.Get_LastDigit(9));
            Assert::AreEqual(3, exercise.Get_LastDigit(-123));  // should work with negative
        }

        TEST_METHOD(OurEx2IsEvenDigit_ValidDigits_Success)
        {
            // Arrange
            miit::algebra::OurEx2 exercise(0, std::make_unique<miit::algebra::ConstantGenerator>(0));

            // Act & Assert
            Assert::IsTrue(exercise.Is_Even_Digit(2));
            Assert::IsTrue(exercise.Is_Even_Digit(4));
            Assert::IsTrue(exercise.Is_Even_Digit(6));
            Assert::IsTrue(exercise.Is_Even_Digit(8));
            Assert::IsTrue(exercise.Is_Even_Digit(0));

            Assert::IsFalse(exercise.Is_Even_Digit(1));
            Assert::IsFalse(exercise.Is_Even_Digit(3));
            Assert::IsFalse(exercise.Is_Even_Digit(5));
            Assert::IsFalse(exercise.Is_Even_Digit(7));
            Assert::IsFalse(exercise.Is_Even_Digit(9));
        }

        TEST_METHOD(OurEx2Task_RemovesElementsWithEvenFirstAndLastDigits_Success)
        {
            // Arrange
            auto generator = std::make_unique<miit::algebra::ConstantGenerator>(0);
            miit::algebra::OurEx2 exercise(6, std::move(generator));

            // Manually set matrix values
            auto& matrix = const_cast<miit::algebra::Matrix<int>&>(exercise.get_matrix());
            matrix[0] = 246;  // first=2 (even), last=6 (even) - should be removed
            matrix[1] = 135;  // first=1 (odd), last=5 (odd) - should be kept
            matrix[2] = 468;  // first=4 (even), last=8 (even) - should be removed
            matrix[3] = 123;  // first=1 (odd), last=3 (odd) - should be kept
            matrix[4] = 222;  // first=2 (even), last=2 (even) - should be removed
            matrix[5] = 357;  // first=3 (odd), last=7 (odd) - should be kept

            // Act
            exercise.Task();

            // Assert - only elements with odd first and last digits should remain
            const auto& result = exercise.get_matrix();
            Assert::AreEqual(size_t(3), result.get_size());
            Assert::AreEqual(135, result[0]);
            Assert::AreEqual(123, result[1]);
            Assert::AreEqual(357, result[2]);
        }
    };

    TEST_CLASS(OurEx3Tests)
    {
    public:
        TEST_METHOD(OurEx3Task_AppliesTransformationRules_Success)
        {
            // Arrange
            auto generator = std::make_unique<miit::algebra::ConstantGenerator>(0);
            miit::algebra::OurEx3 exercise(15, std::move(generator));

            // Manually set matrix values
            auto& matrix = const_cast<miit::algebra::Matrix<int>&>(exercise.get_matrix());
            for (size_t i = 0; i < 15; ++i) {
                matrix[i] = static_cast<int>(i) + 1;  // values 1 to 15
            }

            // Act
            exercise.Task();

            // Assert
            // For indices 0-1 and 12-14: value = value - 1
            Assert::AreEqual(0, matrix[0]);   // 1-1=0
            Assert::AreEqual(1, matrix[1]);   // 2-1=1

            // For indices 2-11: value = -value * value
            Assert::AreEqual(-9, matrix[2]);   // -(3*3) = -9
            Assert::AreEqual(-16, matrix[3]);  // -(4*4) = -16
            Assert::AreEqual(-25, matrix[4]);  // -(5*5) = -25
            Assert::AreEqual(-36, matrix[5]);  // -(6*6) = -36
            Assert::AreEqual(-49, matrix[6]);  // -(7*7) = -49
            Assert::AreEqual(-64, matrix[7]);  // -(8*8) = -64
            Assert::AreEqual(-81, matrix[8]);  // -(9*9) = -81
            Assert::AreEqual(-100, matrix[9]); // -(10*10) = -100
            Assert::AreEqual(-121, matrix[10]); // -(11*11) = -121
            Assert::AreEqual(-144, matrix[11]); // -(12*12) = -144

            // For indices 12-14: value = value - 1
            Assert::AreEqual(12, matrix[12]); // 13-1=12
            Assert::AreEqual(13, matrix[13]); // 14-1=13
            Assert::AreEqual(14, matrix[14]); // 15-1=14
        }

        TEST_METHOD(OurEx3Task_SmallArray_Success)
        {
            // Arrange
            auto generator = std::make_unique<miit::algebra::ConstantGenerator>(0);
            miit::algebra::OurEx3 exercise(2, std::move(generator));

            // Manually set matrix values
            auto& matrix = const_cast<miit::algebra::Matrix<int>&>(exercise.get_matrix());
            matrix[0] = 5;
            matrix[1] = 10;

            // Act
            exercise.Task();

            // Assert - both indices should use value-1 rule
            Assert::AreEqual(4, matrix[0]);  // 5-1=4
            Assert::AreEqual(9, matrix[1]);  // 10-1=9
        }
    };

    TEST_CLASS(IntegrationTests)
    {
    public:
        TEST_METHOD(FullPipeline_RandomGeneratorAndTask1_Success)
        {
            // Arrange
            auto generator = std::make_unique<miit::algebra::RandomGenerator>(1, 100);
            miit::algebra::OurEx1 exercise(10, std::move(generator));

            // Act
            exercise.fill_matrix();
            exercise.Task();

            // Assert - should complete without throwing
            Assert::IsTrue(exercise.get_matrix().get_size() == 10);
        }

        TEST_METHOD(FullPipeline_ConstantGeneratorAndTask2_Success)
        {
            // Arrange
            auto generator = std::make_unique<miit::algebra::ConstantGenerator>(135); // odd first and last digits
            miit::algebra::OurEx2 exercise(5, std::move(generator));

            // Act
            exercise.fill_matrix();
            exercise.Task();

            // Assert - all elements should be kept (135 has odd first and last digits)
            Assert::AreEqual(size_t(5), exercise.get_matrix().get_size());
            Assert::AreEqual(135, exercise.get_matrix()[0]);
        }
    };
}