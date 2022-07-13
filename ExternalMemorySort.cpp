#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <bits/stdc++.h>


using namespace std;

struct EmpBlock {
    int eid;
    string ename;
    int age;
    double salary;
};

struct DeptBlock {
    int did;
    string dname;
    double budget;
    int managerid;
};


// Grab a single block from the emp.csv file, in theory if a block was larger than
// one tuple, this function would return an array of EmpBlocks and the entire if
// and else statement would be wrapped in a loop for x times based on block size
EmpBlock grabEmp(fstream &empin) {
    string line, word;
    EmpBlock emp;
    // grab entire line
    if (getline(empin, line, '\n')) {
        // turn line into a stream
        stringstream s(line);
        // gets everything in stream up to comma
        getline(s, word,',');
        emp.eid = stoi(word);
        getline(s, word, ',');
        emp.ename = word;
        getline(s, word, ',');
        emp.age = stoi(word);
        getline(s, word, ',');
        emp.salary = stod(word);
        return emp;
    } else {
        emp.eid = -1;
        return emp;
    }
}
/*
// Grab a single block from the dept.csv file, in theory if a block was larger than
// one tuple, this function would return an array of DeptBlocks and the entire if
// and else statement would be wrapped in a loop for x times based on block size
DeptBlock grabDept(fstream &deptin) {
    string line, word;
    DeptBlock dept;
    if (getline(deptin, line, '\n')) {
        stringstream s(line);
        getline(s, word,',');
        dept.did = stoi(word);
        getline(s, word, ',');
        dept.dname = word;
        getline(s, word, ',');
        dept.budget = stod(word);
        getline(s, word, ',');
        dept.managerid = stoi(word);
        return dept;
    } else {
        dept.did = -1;
        return dept;
    }
}
*/
//Print out the attributes from emp and dept when a join condition is met
void printJoin(EmpBlock emp, DeptBlock dept, fstream &fout) {
    fout << emp.eid << ',' << emp.ename << ',' << emp.age << ','
        << emp.salary << ',' << dept.did << ',' << dept.dname << ','
        << dept.budget << "\n";
}

bool emp_cmp(const EmpBlock &a, const EmpBlock &b)
{
    return a.eid < b.eid;
}
/*
bool dept_cmp(const DeptBlock &a, const DeptBlock &b)
{
    return a.managerid < b.managerid;
}
*/
void showEmp(vector <EmpBlock> eblocks)
{
    for(int i = 0; i < eblocks.size(); i++)
    {
        cout << i << ": " << eblocks[i].eid << endl;
    }
}

void emp_buffer(vector <EmpBlock> eblocks, fstream &buf)
{
    //fstream buf;
    //buf.open("emp_buf" + to_string(run - 1) + ".csv", ios::out | ios::app);
    for(int i = 0; i < eblocks.size(); i++)
    {
        buf << eblocks[i].eid    << ","
            << eblocks[i].ename  << ","
            << eblocks[i].age    << ","
            << eblocks[i].salary
            << "\n";
    }
}

void emp_write_block(EmpBlock b, int ph, int phase_total)
{
    fstream buf;
    if (ph + 1 == phase_total) {
        buf.open("EmpSorted.csv", ios::out | ios::app);
    }
    else {
        buf.open("emp_buf" + to_string(ph + 1) + ".csv", ios::out | ios::app);
    }

    buf << b.eid    << ","
        << b.ename  << ","
        << b.age    << ","
        << b.salary
        << "\n";
    buf.close();
}
/*
void dept_buffer(vector <DeptBlock> dblocks, fstream &buf)
{
    //fstream buf;
    //buf.open("dept_buf" + to_string(run - 1) + ".csv", ios::out | ios::app);
    for(int i = 0; i < dblocks.size(); i++)
    {
        buf << dblocks[i].did    << ","
            << dblocks[i].dname  << ","
            << dblocks[i].budget    << ","
            << dblocks[i].managerid
            << "\n";
    }
}
*/
EmpBlock emp_spcline(int line, int ph)
{
    int count = 0;
    EmpBlock b;
    fstream buf;
    buf.open("emp_buf" + to_string(ph) + ".csv", ios::in);
    while(true) {
        b = grabEmp(buf);
        //cout << b.eid << endl;
        if (b.eid == -1) {
            buf.close();
            return b;
        }
        if (count == line) {
            buf.close();
            return b;
        }
        count++;
    }
}
/*
DeptBlock dept_spcline(int line)
{
    int count = 0;
    DeptBlock b;
    fstream buf;
    buf.open("dept_buf.csv", ios::in);
    while(true) {
        b = grabDept(buf);
        if(b.did == -1)
            break;
        if(count == line)
            return b;
        count++;
    }
    return b;
}
*/

void dumps(fstream &f, int start)
{

}

int main() {
  int phase = 0;
  int phase_total = 0;
  int emp_total = 0;
  int emp_min_ind = 0;
  int emp_min_eid = 0;
  vector <int>        emp_seek;
  vector <int>        blocks_ph;
  vector <EmpBlock>   eblocks;
  fstream empin;
  fstream emp_buf;
  empin.open("Emp.csv", ios::in);
  emp_buf.open("emp_buf" + to_string(phase) + ".csv", ios::out | ios::app);
  EmpBlock  empblock;
  //int dept_min_mid = 0;
  //int dept_min_ind = 0;
  //vector <int>        dept_seek;
  //int dept_total = 0;
  //vector <DeptBlock>  dblocks;
  // open file streams to read and write
  //fstream deptin;
  //fstream joinout;
  //fstream dept_buf;
  //deptin.open("Dept.csv", ios::in);
  //joinout.open("EmpSort.csv", ios::out | ios::app);
  //dept_buf.open("dept_buf.csv", ios::out | ios::app);
  //DeptBlock deptblock;
  // flags check when relations are done being read
  bool flag = true;
  while (flag) {
      // for block in relation emp

      // grabs a block
      empblock = grabEmp(empin);
      if (empblock.eid == -1) {
          emp_total += eblocks.size();
          sort(eblocks.begin(), eblocks.end(), emp_cmp);
          emp_buffer(eblocks, emp_buf);
          eblocks.clear();
          flag = false;
          break;
      }
      eblocks.push_back(empblock);
      // checks if filestream is empty
      if (eblocks.size() % 21 == 0 && eblocks.size() != 0) {
          emp_total += eblocks.size();
          sort(eblocks.begin(), eblocks.end(), emp_cmp);
          emp_buffer(eblocks, emp_buf);
          eblocks.clear();
      }
  }

  float t = emp_total;
  //cout << "emp_total: " << emp_total << endl;
  blocks_ph.push_back(t);
  while(true) {
    //cout << "t: " << t << endl;
    if(t / 21 > 1) {
        t /= 21;
        t = round(t + 0.5);
        phase_total++;
    }
    else if (t / 21 == 1) {
        t /= 21;
        phase_total++;
    }
    else if(t / 21 > 0  && t / 21 <= 1) {
        //phase_total++;
        //blocks_ph.push_back(1);
        break;
    }
    blocks_ph.push_back(t);
  }
  empin.close();
  emp_buf.close();


  //cout << phase_total << endl;
  for(int ph = 0; ph < phase_total; ph++) {
    //cout << "ph: " << ph << "  blocks_ph: " << blocks_ph[ph] << endl;
    bool tail = false;
    // INPUT FILE
    empin.open("emp_buf" + to_string(ph) + ".csv", ios::in);
    // OUTPUT FILE
    if (ph + 1 == phase_total) {
        emp_buf.open("EmpSorted.csv", ios::out | ios::app);
    }
    else {
        emp_buf.open("emp_buf" + to_string(ph + 1) + ".csv", ios::out | ios::app);
    }
    // Set seek in 21 runs(blocks)
    for(int i = 0; i < emp_total; i++) {
        if (i % int(pow(21, ph + 1)) == 0) {
            emp_seek.push_back(i);
        }
    }

    for(int run = 0; run < emp_seek.size(); run++) {
        eblocks.push_back(emp_spcline(emp_seek[run], ph));
        //cout << "run: " << run << endl;
        if (run != 0 && run % int(pow(21, ph + 1)) == 0 || run == emp_seek.size() - 1) {
            //cout << "------------- " << endl;
            //cout << "emp_seek size(): " << emp_seek.size() << endl;
            //showEmp(eblocks);
            bool end = false;
            while (!end) {
                if (run == emp_seek.size() - 1) {
                    for(int i = 0; i < emp_seek.size(); i++) {
                        if (eblocks[i].eid < eblocks[emp_min_ind].eid)
                        emp_min_ind = i;
                    }
                }
                else {
                    for(int i = run - int(pow(21, ph + 1)); i < run; i++) {
                        //cout << "i: " << i << endl;
                        //cout << eblocks[i].eid << endl;
                        if (eblocks[i].eid < eblocks[emp_min_ind].eid)
                            emp_min_ind = i;
                    }
                }
                //cout << "min index: " << emp_min_ind << endl;
                emp_min_eid = eblocks[emp_min_ind].eid;
                /*
                if (emp_min_eid == -1 && tail) {
                    emp_min_ind--;
                    emp_seek.pop_back();
                    eblocks.pop_back();
                }
                */
                emp_write_block(eblocks[emp_min_ind], ph, phase_total);
                eblocks.erase(eblocks.begin() + emp_min_ind);
                emp_seek[emp_min_ind]++;
                if (emp_seek[emp_min_ind] % int(pow(21, ph + 1)) == 0 || emp_seek[emp_min_ind] == emp_total) {
                    EmpBlock b;
                    b.eid = INT_MAX;
                    eblocks.insert(eblocks.begin() + emp_min_ind, b);
                }
                else {
                    eblocks.insert(eblocks.begin() + emp_min_ind, emp_spcline(emp_seek[emp_min_ind], ph));
                }
                /*
                for(int i = run - 21; i < run; i++) {
                    cout << "<" << i << "> emp seek: " << emp_seek[i] << endl;
                }
                */
                if (run == emp_seek.size() - 1) {
                    for(int i = 0; i < emp_seek.size(); i++) {
                        if((emp_seek[i]) % int(pow(21, ph + 1)) == 0 || emp_seek[i] == emp_total) {
                            end = true;
                        }
                        else {
                            end = false;
                            break;
                        }
                    }
                }
                else {
                    for(int i = run - int(pow(21, ph + 1)); i < run; i++) {
                        if((emp_seek[i]) % int(pow(21, ph + 1)) == 0 || emp_seek[i] == emp_total) {
                            end = true;
                        }
                        else {
                            end = false;
                            break;
                        }
                    }
                }
            }
        }
    }

    empin.close();
    emp_buf.close();
    eblocks.clear();
    emp_seek.clear();
  }
  return 0;
}
