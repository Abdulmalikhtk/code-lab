// Online C++ compiler to run C++ program online
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Patient
{
  public:
  string p_name;
  int p_age;

  Patient(string name,int age)
  {
      p_name=name;
      p_age=age;
      cout<<"Patient Registered:"<<p_name<<" ,"<<p_age<<endl;
  }
  ~Patient()
  {
   cout<<"Patient record deleted"<<endl;
  }
  void showpatient() const
  {
      cout<<"Patient Details-> Name:"<<p_name<<" , Age:"<<p_age<<endl;
  }

};
class Department
{
public:
string dept_name;

Department(string name)
{
    dept_name=name;
}
void accesspoint(shared_ptr<Patient> sp)
{
    cout<<dept_name<<" is accessing patient Details"<<endl;
    sp->showpatient();
}
};
class Visitor
{
    public:
    weak_ptr<Patient> visitior;

    Visitor(weak_ptr<Patient> vp)
    {
     visitior=vp;
    }
    void vistordetails()
    {
        if(auto Patient=visitior.lock())
        {
            cout<<"Vister visiting patient :";

            Patient->showpatient();
        }
    }
};

class Bed
{
  public:
  unique_ptr<Patient> bedpatient;

  Bed(unique_ptr<Patient> patient)
  {
      bedpatient=move(patient);
  }
  void bedetails() const
  {
      if(bedpatient)
      {
          cout<<"Bed Assigned to ";
          bedpatient->showpatient();
      }
  }
};
int main() {
    cout << "\n📋 Hospital System Initialized\n";
    vector<shared_ptr<Patient>> patientList;
    patientList.push_back(make_shared<Patient>("alice",30));
    patientList.push_back(make_shared<Patient>("bob",26));
    patientList.push_back(make_shared<Patient>("charlie",40));

    Department cardio("cardiology");
    Department neuro("Neurology");
    for(auto patient : patientList)
    {
     cardio.accesspoint(patient);
     neuro.accesspoint(patient);
    }

    Visitor visit(patientList[1]);
    visit.vistordetails();

    vector<Bed> beds;

    beds.emplace_back(make_unique<Patient>("test1",21));
    beds.emplace_back(make_unique<Patient>("test2",22));
    beds.emplace_back(make_unique<Patient>("test3",23));

    for(const auto& bed: beds)
    {
    bed.bedetails();
    }

    std::cout << "\n🔚 End of main function\n";
    return 0;
}
