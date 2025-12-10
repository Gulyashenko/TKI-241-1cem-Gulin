#include "CppUnitTest.h"
#include "../library/Person.h"
#include "../library/Patient.h"
#include "../library/MedicalWorker.h"
#include "../library/Hospital.h"
#include <sstream>
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HospitalTests
{
    TEST_CLASS(PersonTests)
    {
    public:
        TEST_METHOD(PersonConstructor_ValidData_Success)
        {
            // Arrange & Act
            Person person("John Doe", 30);
            
            // Assert
            Assert::AreEqual(std::string("John Doe"), person.getName());
            Assert::AreEqual(30, person.getAge());
        }

        TEST_METHOD(PersonDefaultConstructor_Success)
        {
            // Arrange & Act
            Person person;
            
            // Assert
            Assert::AreEqual(std::string(""), person.getName());
            Assert::AreEqual(0, person.getAge());
        }

        TEST_METHOD(PersonPrintInfo_ValidData_OutputsCorrectInfo)
        {
            // Arrange
            Person person("Alice", 25);
            std::ostringstream os;
            
            // Act
            person.printInfo();
            os << person;
            
            // Assert
            std::string result = os.str();
            Assert::IsTrue(result.find("Name: Alice") != std::string::npos);
            Assert::IsTrue(result.find("Age: 25") != std::string::npos);
        }

        TEST_METHOD(PersonStreamInputOutput_Success)
        {
            // Arrange
            Person person;
            std::stringstream ss;
            ss << "Alice\n25\n";
            
            // Act
            ss >> person;
            
            // Assert
            Assert::AreEqual(std::string("Alice"), person.getName());
            Assert::AreEqual(25, person.getAge());
        }
    };

    TEST_CLASS(PatientTests)
    {
    public:
        TEST_METHOD(PatientConstructor_ValidData_Success)
        {
            // Arrange & Act
            Patient patient("John Smith", 45, 101);
            
            // Assert
            Assert::AreEqual(std::string("John Smith"), patient.getName());
            Assert::AreEqual(45, patient.getAge());
            Assert::AreEqual(101, patient.getRoomNumber());
            Assert::IsTrue(patient.getId() >= 1000); // Стартовый ID
        }

        TEST_METHOD(PatientDefaultConstructor_Success)
        {
            // Arrange & Act
            Patient patient1;
            Patient patient2;
            
            // Assert
            Assert::AreEqual(std::string(""), patient1.getName());
            Assert::AreEqual(0, patient1.getAge());
            Assert::AreEqual(0, patient1.getRoomNumber());
            Assert::IsTrue(patient2.getId() > patient1.getId()); // ID увеличивается
        }

        TEST_METHOD(PatientPrintInfo_ValidData_OutputsCorrectInfo)
        {
            // Arrange
            Patient patient("Bob Wilson", 50, 202);
            std::ostringstream os;
            
            // Act
            patient.printInfo();
            os << patient;
            
            // Assert
            std::string result = os.str();
            Assert::IsTrue(result.find("Patient [ID:") != std::string::npos);
            Assert::IsTrue(result.find("Room: 202") != std::string::npos);
            Assert::IsTrue(result.find("Name: Bob Wilson") != std::string::npos);
        }

        TEST_METHOD(PatientStreamInputOutput_Success)
        {
            // Arrange
            Patient patient;
            std::stringstream ss;
            ss << "Charlie Brown\n35\n305\n";
            
            // Act
            ss >> patient;
            
            // Assert
            Assert::AreEqual(std::string("Charlie Brown"), patient.getName());
            Assert::AreEqual(35, patient.getAge());
            Assert::AreEqual(305, patient.getRoomNumber());
        }

        TEST_METHOD(PatientIdIncrementation_Success)
        {
            // Arrange & Act
            Patient patient1("Patient1", 20, 1);
            Patient patient2("Patient2", 30, 2);
            Patient patient3("Patient3", 40, 3);
            
            // Assert
            Assert::IsTrue(patient2.getId() == patient1.getId() + 1);
            Assert::IsTrue(patient3.getId() == patient2.getId() + 1);
        }
    };

    TEST_CLASS(MedicalWorkerTests)
    {
    public:
        TEST_METHOD(MedicalWorkerConstructor_ValidData_Success)
        {
            // Arrange & Act
            MedicalWorker doctor("Dr. Smith", 40, "Cardiology");
            
            // Assert
            Assert::AreEqual(std::string("Dr. Smith"), doctor.getName());
            Assert::AreEqual(40, doctor.getAge());
            Assert::AreEqual(std::string("Cardiology"), doctor.getSpecialization());
            Assert::AreEqual(0, doctor.getPatientCount());
        }

        TEST_METHOD(MedicalWorkerDefaultConstructor_Success)
        {
            // Arrange & Act
            MedicalWorker worker;
            
            // Assert
            Assert::AreEqual(std::string(""), worker.getName());
            Assert::AreEqual(0, worker.getAge());
            Assert::AreEqual(std::string(""), worker.getSpecialization());
            Assert::AreEqual(0, worker.getPatientCount());
        }

        TEST_METHOD(MedicalWorkerCopyConstructor_Success)
        {
            // Arrange
            MedicalWorker original("Dr. Jones", 45, "Neurology");
            Patient patient("John Doe", 50, 101);
            original.addPatient(patient);
            
            // Act
            MedicalWorker copy(original);
            
            // Assert
            Assert::AreEqual(original.getName(), copy.getName());
            Assert::AreEqual(original.getAge(), copy.getAge());
            Assert::AreEqual(original.getSpecialization(), copy.getSpecialization());
            Assert::AreEqual(original.getPatientCount(), copy.getPatientCount());
        }

        TEST_METHOD(MedicalWorkerMoveConstructor_Success)
        {
            // Arrange
            MedicalWorker original("Dr. Brown", 35, "Pediatrics");
            Patient patient("Child", 5, 102);
            original.addPatient(patient);
            
            // Act
            MedicalWorker moved(std::move(original));
            
            // Assert
            Assert::AreEqual(std::string("Dr. Brown"), moved.getName());
            Assert::AreEqual(35, moved.getAge());
            Assert::AreEqual(std::string("Pediatrics"), moved.getSpecialization());
            Assert::AreEqual(1, moved.getPatientCount());
            Assert::AreEqual(0, original.getPatientCount());
        }

        TEST_METHOD(MedicalWorkerAddPatient_Success)
        {
            // Arrange
            MedicalWorker doctor("Dr. White", 50, "Surgery");
            Patient patient1("Patient1", 30, 201);
            Patient patient2("Patient2", 40, 202);
            
            // Act
            doctor.addPatient(patient1);
            doctor.addPatient(patient2);
            
            // Assert
            Assert::AreEqual(2, doctor.getPatientCount());
            const Patient* patients = doctor.getPatients();
            Assert::AreEqual(std::string("Patient1"), patients[0].getName());
            Assert::AreEqual(std::string("Patient2"), patients[1].getName());
        }

        TEST_METHOD(MedicalWorkerRemovePatient_Success)
        {
            // Arrange
            MedicalWorker doctor("Dr. Black", 55, "Oncology");
            Patient patient1("Patient1", 60, 301);
            Patient patient2("Patient2", 65, 302);
            Patient patient3("Patient3", 70, 303);
            
            doctor.addPatient(patient1);
            doctor.addPatient(patient2);
            doctor.addPatient(patient3);
            
            // Act
            doctor.removePatient(1); // Удаляем пациента с индексом 1 (Patient2)
            
            // Assert
            Assert::AreEqual(2, doctor.getPatientCount());
            const Patient* patients = doctor.getPatients();
            Assert::AreEqual(std::string("Patient1"), patients[0].getName());
            Assert::AreEqual(std::string("Patient3"), patients[1].getName());
        }

        TEST_METHOD(MedicalWorkerHasPatient_Success)
        {
            // Arrange
            MedicalWorker doctor("Dr. Green", 38, "Dermatology");
            Patient patient1("Alice", 25, 401);
            Patient patient2("Bob", 30, 402);
            
            doctor.addPatient(patient1);
            doctor.addPatient(patient2);
            
            // Act & Assert
            Assert::IsTrue(doctor.hasPatient("Alice"));
            Assert::IsTrue(doctor.hasPatient("Bob"));
            Assert::IsFalse(doctor.hasPatient("Charlie"));
        }

        TEST_METHOD(MedicalWorkerResizePatients_Success)
        {
            // Arrange
            MedicalWorker doctor("Dr. Blue", 42, "Orthopedics");
            
            // Act - добавляем больше пациентов, чем начальная емкость (2)
            for (int i = 0; i < 5; i++) {
                Patient patient("Patient" + std::to_string(i), 20 + i, 500 + i);
                doctor.addPatient(patient);
            }
            
            // Assert
            Assert::AreEqual(5, doctor.getPatientCount());
            const Patient* patients = doctor.getPatients();
            for (int i = 0; i < 5; i++) {
                Assert::IsTrue(patients[i].getName().find("Patient") != std::string::npos);
            }
        }

        TEST_METHOD(MedicalWorkerStreamInputOutput_Success)
        {
            // Arrange
            MedicalWorker worker;
            std::stringstream ss;
            ss << "Dr. Taylor\n48\nRadiology\n";
            
            // Act
            ss >> worker;
            
            // Assert
            Assert::AreEqual(std::string("Dr. Taylor"), worker.getName());
            Assert::AreEqual(48, worker.getAge());
            Assert::AreEqual(std::string("Radiology"), worker.getSpecialization());
        }

        TEST_METHOD(MedicalWorkerPrintInfo_ValidData_OutputsCorrectInfo)
        {
            // Arrange
            MedicalWorker doctor("Dr. Miller", 52, "Cardiology");
            Patient patient("Heart Patient", 60, 601);
            doctor.addPatient(patient);
            
            std::ostringstream os;
            
            // Act
            doctor.printInfo();
            os << doctor;
            
            // Assert
            std::string result = os.str();
            Assert::IsTrue(result.find("Medical Worker:") != std::string::npos);
            Assert::IsTrue(result.find("Name: Dr. Miller") != std::string::npos);
            Assert::IsTrue(result.find("Specialization: Cardiology") != std::string::npos);
            Assert::IsTrue(result.find("Patients: 1") != std::string::npos);
        }
    };

    TEST_CLASS(HospitalTests)
    {
    public:
        TEST_METHOD(HospitalDefaultConstructor_Success)
        {
            // Arrange & Act
            Hospital hospital;
            
            // Assert
            Assert::AreEqual(0, hospital.getWorkerCount());
        }

        TEST_METHOD(HospitalAddWorker_Success)
        {
            // Arrange
            Hospital hospital;
            MedicalWorker doctor1("Dr. Adams", 45, "Neurology");
            MedicalWorker doctor2("Dr. Baker", 50, "Cardiology");
            
            // Act
            hospital.addWorker(doctor1);
            hospital.addWorker(doctor2);
            
            // Assert
            Assert::AreEqual(2, hospital.getWorkerCount());
            const MedicalWorker* workers = hospital.getWorkers();
            Assert::AreEqual(std::string("Dr. Adams"), workers[0].getName());
            Assert::AreEqual(std::string("Dr. Baker"), workers[1].getName());
        }

        TEST_METHOD(HospitalRemoveWorker_Success)
        {
            // Arrange
            Hospital hospital;
            MedicalWorker doctor1("Dr. Clark", 40, "Pediatrics");
            MedicalWorker doctor2("Dr. Davis", 55, "Surgery");
            MedicalWorker doctor3("Dr. Evans", 48, "Orthopedics");
            
            hospital.addWorker(doctor1);
            hospital.addWorker(doctor2);
            hospital.addWorker(doctor3);
            
            // Act
            hospital.removeWorker(1); // Удаляем доктора с индексом 1 (Dr. Davis)
            
            // Assert
            Assert::AreEqual(2, hospital.getWorkerCount());
            const MedicalWorker* workers = hospital.getWorkers();
            Assert::AreEqual(std::string("Dr. Clark"), workers[0].getName());
            Assert::AreEqual(std::string("Dr. Evans"), workers[1].getName());
        }

        TEST_METHOD(HospitalFindWorkerByName_Success)
        {
            // Arrange
            Hospital hospital;
            MedicalWorker doctor1("Dr. Fisher", 42, "Dermatology");
            MedicalWorker doctor2("Dr. Garcia", 47, "Oncology");
            
            hospital.addWorker(doctor1);
            hospital.addWorker(doctor2);
            
            // Act
            MedicalWorker* found1 = hospital.findWorkerByName("Dr. Fisher");
            MedicalWorker* found2 = hospital.findWorkerByName("Dr. Garcia");
            MedicalWorker* notFound = hospital.findWorkerByName("Dr. Unknown");
            
            // Assert
            Assert::IsNotNull(found1);
            Assert::AreEqual(std::string("Dr. Fisher"), found1->getName());
            
            Assert::IsNotNull(found2);
            Assert::AreEqual(std::string("Dr. Garcia"), found2->getName());
            
            Assert::IsNull(notFound);
        }

        TEST_METHOD(HospitalFindWorkerByPatientName_Success)
        {
            // Arrange
            Hospital hospital;
            MedicalWorker doctor1("Dr. Harris", 51, "Cardiology");
            MedicalWorker doctor2("Dr. Irving", 44, "Neurology");
            
            Patient patient1("John", 60, 101);
            Patient patient2("Mary", 65, 102);
            
            doctor1.addPatient(patient1);
            doctor2.addPatient(patient2);
            
            hospital.addWorker(doctor1);
            hospital.addWorker(doctor2);
            
            // Act
            MedicalWorker* found1 = hospital.findWorkerByPatientName("John");
            MedicalWorker* found2 = hospital.findWorkerByPatientName("Mary");
            MedicalWorker* notFound = hospital.findWorkerByPatientName("Unknown");
            
            // Assert
            Assert::IsNotNull(found1);
            Assert::AreEqual(std::string("Dr. Harris"), found1->getName());
            
            Assert::IsNotNull(found2);
            Assert::AreEqual(std::string("Dr. Irving"), found2->getName());
            
            Assert::IsNull(notFound);
        }

        TEST_METHOD(HospitalCopyConstructor_Success)
        {
            // Arrange
            Hospital original;
            MedicalWorker doctor("Dr. Johnson", 53, "Surgery");
            Patient patient("PatientX", 70, 201);
            doctor.addPatient(patient);
            original.addWorker(doctor);
            
            // Act
            Hospital copy(original);
            
            // Assert
            Assert::AreEqual(original.getWorkerCount(), copy.getWorkerCount());
            const MedicalWorker* originalWorkers = original.getWorkers();
            const MedicalWorker* copyWorkers = copy.getWorkers();
            Assert::AreEqual(originalWorkers[0].getName(), copyWorkers[0].getName());
            Assert::AreEqual(originalWorkers[0].getPatientCount(), copyWorkers[0].getPatientCount());
        }

        TEST_METHOD(HospitalMoveConstructor_Success)
        {
            // Arrange
            Hospital original;
            MedicalWorker doctor("Dr. King", 49, "Pediatrics");
            original.addWorker(doctor);
            
            // Act
            Hospital moved(std::move(original));
            
            // Assert
            Assert::AreEqual(1, moved.getWorkerCount());
            Assert::AreEqual(0, original.getWorkerCount());
        }

        TEST_METHOD(HospitalPrintAllWorkers_Success)
        {
            // Arrange
            Hospital hospital;
            MedicalWorker doctor1("Dr. Lewis", 46, "Radiology");
            MedicalWorker doctor2("Dr. Martin", 54, "Oncology");
            
            hospital.addWorker(doctor1);
            hospital.addWorker(doctor2);
            
            std::ostringstream os;
            
            // Act
            hospital.printAllWorkers();
            
            // Assert - проверяем, что функция выполняется без ошибок
            Assert::AreEqual(2, hospital.getWorkerCount());
        }

        TEST_METHOD(HospitalPrintAllPatients_Success)
        {
            // Arrange
            Hospital hospital;
            MedicalWorker doctor("Dr. Nelson", 43, "Cardiology");
            
            Patient patient1("PatientA", 55, 301);
            Patient patient2("PatientB", 60, 302);
            
            doctor.addPatient(patient1);
            doctor.addPatient(patient2);
            
            hospital.addWorker(doctor);
            
            std::ostringstream os;
            
            // Act
            hospital.printAllPatients();
            
            // Assert - проверяем, что функция выполняется без ошибок
            Assert::AreEqual(1, hospital.getWorkerCount());
        }

        TEST_METHOD(HospitalPrintPatientsOfWorker_Success)
        {
            // Arrange
            Hospital hospital;
            MedicalWorker doctor("Dr. Owens", 57, "Neurology");
            
            Patient patient("PatientC", 65, 401);
            doctor.addPatient(patient);
            
            hospital.addWorker(doctor);
            
            std::ostringstream os;
            
            // Act
            hospital.printPatientsOfWorker("Dr. Owens");
            
            // Assert - проверяем, что функция выполняется без ошибок
            Assert::AreEqual(1, hospital.getWorkerCount());
        }

        TEST_METHOD(HospitalPrintWorkerByPatientName_Success)
        {
            // Arrange
            Hospital hospital;
            MedicalWorker doctor("Dr. Parker", 52, "Orthopedics");
            
            Patient patient("PatientD", 70, 501);
            doctor.addPatient(patient);
            
            hospital.addWorker(doctor);
            
            std::ostringstream os;
            
            // Act
            hospital.printWorkerByPatientName("PatientD");
            
            // Assert - проверяем, что функция выполняется без ошибок
            Assert::AreEqual(1, hospital.getWorkerCount());
        }

        TEST_METHOD(HospitalPrintPatientsByRoom_Success)
        {
            // Arrange
            Hospital hospital;
            MedicalWorker doctor("Dr. Quinn", 48, "Dermatology");
            
            Patient patient1("PatientE", 35, 601);
            Patient patient2("PatientF", 40, 602);
            
            doctor.addPatient(patient1);
            doctor.addPatient(patient2);
            
            hospital.addWorker(doctor);
            
            std::ostringstream os;
            
            // Act
            hospital.printPatientsByRoom();
            
            // Assert - проверяем, что функция выполняется без ошибок
            Assert::AreEqual(1, hospital.getWorkerCount());
        }

        TEST_METHOD(HospitalStreamOutput_Success)
        {
            // Arrange
            Hospital hospital;
            MedicalWorker doctor("Dr. Roberts", 56, "Surgery");
            Patient patient("PatientG", 75, 701);
            doctor.addPatient(patient);
            hospital.addWorker(doctor);
            
            std::ostringstream os;
            
            // Act
            os << hospital;
            
            // Assert
            std::string result = os.str();
            Assert::IsTrue(result.find("HOSPITAL STATUS") != std::string::npos);
            Assert::IsTrue(result.find("Total workers: 1") != std::string::npos);
            Assert::IsTrue(result.find("Total patients: 1") != std::string::npos);
            Assert::IsTrue(result.find("Dr. Roberts") != std::string::npos);
        }

        TEST_METHOD(HospitalResizeWorkers_Success)
        {
            // Arrange
            Hospital hospital;
            
            // Act - добавляем больше работников, чем начальная емкость (2)
            for (int i = 0; i < 5; i++) {
                MedicalWorker doctor("Dr." + std::to_string(i), 40 + i, "Specialty" + std::to_string(i));
                hospital.addWorker(doctor);
            }
            
            // Assert
            Assert::AreEqual(5, hospital.getWorkerCount());
            const MedicalWorker* workers = hospital.getWorkers();
            for (int i = 0; i < 5; i++) {
                Assert::IsTrue(workers[i].getName().find("Dr.") != std::string::npos);
            }
        }
    };

    TEST_CLASS(IntegrationTests)
    {
    public:
        TEST_METHOD(FullHospitalSystem_AddWorkersAndPatients_Success)
        {
            // Arrange
            Hospital hospital;
            
            // Act
            MedicalWorker cardiologist("Dr. Heart", 45, "Cardiology");
            MedicalWorker neurologist("Dr. Brain", 50, "Neurology");
            
            Patient heartPatient("Mr. Heart", 60, 101);
            Patient brainPatient("Mr. Brain", 65, 102);
            
            cardiologist.addPatient(heartPatient);
            neurologist.addPatient(brainPatient);
            
            hospital.addWorker(cardiologist);
            hospital.addWorker(neurologist);
            
            // Assert
            Assert::AreEqual(2, hospital.getWorkerCount());
            
            MedicalWorker* foundCardiologist = hospital.findWorkerByName("Dr. Heart");
            Assert::IsNotNull(foundCardiologist);
            Assert::AreEqual(std::string("Cardiology"), foundCardiologist->getSpecialization());
            
            MedicalWorker* foundByPatient = hospital.findWorkerByPatientName("Mr. Brain");
            Assert::IsNotNull(foundByPatient);
            Assert::AreEqual(std::string("Dr. Brain"), foundByPatient->getName());
        }

        TEST_METHOD(HospitalComplexOperations_Success)
        {
            // Arrange
            Hospital hospital;
            
            // Добавляем врачей
            MedicalWorker doctor1("Dr. Alpha", 40, "General");
            MedicalWorker doctor2("Dr. Beta", 45, "Specialist");
            
            // Добавляем пациентов
            Patient patient1("Patient1", 30, 201);
            Patient patient2("Patient2", 35, 202);
            Patient patient3("Patient3", 40, 203);
            
            doctor1.addPatient(patient1);
            doctor1.addPatient(patient2);
            doctor2.addPatient(patient3);
            
            hospital.addWorker(doctor1);
            hospital.addWorker(doctor2);
            
            // Act & Assert
            Assert::AreEqual(2, hospital.getWorkerCount());
            
            // Удаляем пациента у первого врача
            hospital.getWorkers()[0].removePatient(0);
            Assert::AreEqual(1, hospital.getWorkers()[0].getPatientCount());
            
            // Удаляем врача
            hospital.removeWorker(0);
            Assert::AreEqual(1, hospital.getWorkerCount());
            Assert::AreEqual(std::string("Dr. Beta"), hospital.getWorkers()[0].getName());
        }
    };
}
