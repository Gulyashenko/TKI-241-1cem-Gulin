#include <iostream>
#include "../library/Hospital.h"

enum class Command{
  ShowWorkers = 1,
  ShowWorkersOnPatient = 2,
  ShowPasients = 3,
  ShowPacientsOfWorker = 4,
  ShowRoomOfPatient = 5
};

int input(const char* message);

int main(){
    Hospital hospital;
    std::cin>>hospital;
    
    ctd::cout<<"Enter command:\n" << ShowWorkers << " - show workers\n" << ShowWorkersOnPatient
      << " - show workers on patient\n" << ShowPasients << " - show patients\n" << ShowPacientsOfWorker
      << " - show patients of worker\n" << ShowRoomOfPatient << " - show patients by room\n" << ShowPatient
      << " - show patient\n" << ShowHospital << " - show hospital\n";
    int command = 0;
    std::cin>>command;
    switch (command){
      case ShowWorkers:
      hospital.printAllWorkers();
      break;
      case ShowWorkersOnPatient:
      string patientName;
      std::cin>>patientName;
      hospital.printWorkerByPatientName(patientName);
      break;
      case ShowPasients:
      hospital.printAllPatients();
      break;
      case ShowPacientsOfWorker:
      string workerName;
      std::cin>>workerName;
      hospital.printPatientsOfWorker(workerName);
      break;
      case ShowRoomOfPatient:
      hospital.printPacientsByRoom();
      break;
      default: throw;
    }
    return 0;
  }

int input(const char* message){
  int result = 0;
  if (message != nullptr){ std::cout<<message; }
  std::cin>>result;
  if (std::cin.fail()){std::cout<<"Invalid input\n"; throw;}
  return result;
}
