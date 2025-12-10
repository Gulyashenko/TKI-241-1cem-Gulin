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
    
    ctd::cout<<"Enter command:\n" << ShowWorker << " - show worker\n" << ShowPatient << " - show patient\n" << ShowHospital << " - show hospital\n";
    int command;
    std::cin>>command;
    switch (command){
      case ShowWorkers:
      hospital.printAllWorkers();
      break;
      case ShowWorkersOnPatient:
      string patientName;
      std::cin>>patientName;
      hospital.printWorkerByPatientName();
      break;
      case ShowPasients:
      hospital.printAllPatients();
      break;
      case ShowPacientsOfWorker:
      string workerName;
      std::cin>>workerName;
      hospital.printPatientsOfWorker();
      break;
      case ShowRoomOfPatient:
      hospital.printPacientsByRoom();
      break;
    }
    return 0;
  }

int input(const char* message){
  int result;
  if (message != nullptr){ std::cout<<message; }
  std::cin>>result;
  if (std::cin.fail()){std::cout<<"Invalid input\n"; throw;}
  return result;
}
