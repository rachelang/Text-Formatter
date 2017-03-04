#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void rr(int N, vector<string> &lines, string textFileName);
void j(int N, vector<string> &lines, string textFileName);
void rl(int N, vector<string> &lines, string textFileName);
void c(int N, vector<string> &lines, string textFileName);

void f(vector<string> &lines);
void r(vector<string> &lines);
void p(vector<string> &lines, string c2);
void k(vector<string> &lines, int kIn);
void s(vector<string> &lines, string sIn);

int main (int argc, char* argv[]) {
  int N;
  cin >> N;

  if(N <= 0) {
    cerr << "Error, line length must be positive." << endl;
    return 0;
  }

  string textFileName;
  cin >> textFileName;
  ifstream file(textFileName);
  if(!file) {
    cerr << "Error, cannot open specified text file." << endl;
    return 0;
  }

  string cRead;
  string c1 = "null";
  string c2 = "null";
  string c3 = "null";
  int kIn = 0;
  string sIn = "";
  vector<string> lines;
  vector<string> command;

  while(cin >> cRead) {
    if(cRead=="q") {
      break;
    }
    else if(cRead=="rr"||cRead=="rl"||cRead=="c"||cRead=="j") {
      c1 = cRead;
    }
    else if(cRead=="f"||cRead=="r") {
      c2 = cRead;
    }
    else if(cRead=="p"||cRead=="k"||cRead=="s") {
      c3 = cRead;
      if(c3=="k") cin >> kIn;
      else if(c3=="s") cin >> sIn;

      command.push_back(c1);
      command.push_back(c2);
      command.push_back(c3);
    }
    else {
      cerr << "Error, command is illegal." << endl;
      return 0;
    }
  }

  for(int i=0; i<command.size(); i++) {
      if(command.at(i) == "rr"||command.at(i) == "null") rr(N, lines, textFileName);
      else if(command.at(i) == "j") j(N, lines, textFileName);
      else if(command.at(i) == "rl") rl(N, lines, textFileName);
      else if(command.at(i) == "c") c(N, lines, textFileName);

      if(command.at(i+2) == "p") p(lines, command.at(i+1));
      else if(command.at(i+2) == "k") k(lines, kIn);
      else if(command.at(i+2) == "s") s(lines, sIn);
      i+=2;
      lines.clear();
  }
}

void rr(int N, vector<string> &lines, string textFileName) {
  ifstream file (textFileName);
  if(!file) {
    cerr << "Error, cannot open specified text file." << endl;
  }

  string word;
  vector<string> v;
  int length = 0;
  bool full = false;
  int index = 0;

  while(file >> word) {
    v.push_back(word);
  }

  for(int i=0; i<v.size(); i++) {
    if(full) {
      length = 0;
      full = false;
      index++;
    }
    //cut string if too long
    if(v.at(i).length()>N) {
      v.at(i) = v.at(i).substr(0,N);
    }
    //print string on line if have space
    if(length + v.at(i).length() <= N) {

      if(length==0) lines.push_back(v.at(i));
      else lines.at(index) += v.at(i);

      length += v.at(i).length();
    }
    //checks if full, adds space if not.
    if(i < v.size()-1 && length+1+v.at(i+1).length() <= N) {
      length++;
      lines.at(index) += " ";
    }
    else full = true;
  }
  file.close();

}

void j(int N, vector<string> &lines, string textFileName) {
  ifstream file (textFileName);
  if(!file) {
    cerr << "Error, cannot open specified text file." << endl;
  }

  string word;
  vector<string> v;

  while(file >> word) {
    v.push_back(word);
  }

  int length = 0;
  bool full = false;
  int odd = 0;
  int words = 0, spaces = 0;
  int index = 0;

  for(int i=0; i<v.size(); i++) {
    //cut string if too long
    if(v.at(i).length()>N) {
      v.at(i) = v.at(i).substr(0,N);
    }
    //print string on line if have space
    if(length + v.at(i).length() <= N) {
      length += v.at(i).length();
      words++;
    }
    //checks if full, adds space if not.
    if(i < v.size()-1 && length+1+v.at(i+1).length() <= N) {
      length++;
    }
    else full = true;

    if(full) {
      //length of total words
      length -= words-1;

      if(words-1>0) {
        spaces = (N-length)/(words-1);
      }
      else spaces = N-length;

      if(words-1>0 && (N-length)%(words-1) == 0) {
        odd = 0;
      }
      else if(words-1>0) {
        odd = (N-length)%(words-1);
      }

      for(int j=i+1-words; j<=i; j++) {
        if(j==i+1-words) lines.push_back(v.at(j));
        else lines.at(index) += v.at(j);

        //if not last word on line(when word>1)
        if(j<i || words==1) {
          if(odd>0) {
            lines.at(index) += " ";
            odd--;
          }
          for(int k=0; k<spaces; k++) {
            lines.at(index) += " ";
          }
        }
      }
      index++;

      full = false;
      length = 0;
      odd = 0;
      words = 0;
      spaces = 0;
    }
  }
  file.close();

}

void rl(int N, vector<string> &lines, string textFileName) {
  ifstream file (textFileName);
  if(!file) {
    cerr << "Error, cannot open specified text file." << endl;
  }

  string word;
  vector<string> v;

  while(file >> word) {
    v.push_back(word);
  }

  int length = 0, words = 0;
  bool full = false;
  int index = 0;

  for(int i=0; i<v.size(); i++) {
    //cut string if too long
    if(v.at(i).length()>N) {
      v.at(i) = v.at(i).substr(0,N);
    }
    //print string on line if have space
    if(length + v.at(i).length() <= N) {
      length += v.at(i).length();
      words++;
    }
    //checks if full, adds space if not.
    if(i < v.size()-1 && length+1+v.at(i+1).length() <= N) {
      length++;
    }
    else full = true;

    if(full) {
      for(int k=0; k<N-length; k++) {
        if(k==0) lines.push_back(" ");
        else lines.at(index) += " ";
      }

      for(int j=i+1-words; j<=i; j++) {
        if(v.at(j).length()==N || (j==i+1-words && length==N)) {
          lines.push_back(v.at(j));
        }
        else lines.at(index) += v.at(j);
        if(j<i) lines.at(index) += " ";
      }
      index++;

      full = false;
      length = 0;
      words = 0;
    }
  }
  file.close();

}

void c(int N, vector<string> &lines, string textFileName) {
  ifstream file (textFileName);
  if(!file) {
    cerr << "Error, cannot open specified text file." << endl;
  }

  string word;
  vector<string> v;

  while(file >> word) {
    v.push_back(word);
  }

  int length = 0, words = 0, spaces = 0;
  bool full = false;
  int index = 0;

  for(int i=0; i<v.size(); i++) {
    //cut string if too long
    if(v.at(i).length()>N) {
      v.at(i) = v.at(i).substr(0,N);
    }
    //print string on line if have space
    if(length + v.at(i).length() <= N) {
      length += v.at(i).length();
      words++;
    }
    //checks if full, adds space if not.
    if(i < v.size()-1 && length+1+v.at(i+1).length() <= N) {
      length++;
    }
    else full = true;

    if(full) {
      spaces = (N-length)/2;

      for(int k=0; k<spaces+(N-length)%2; k++) {
        if(k==0) lines.push_back(" ");
        else lines.at(index) += " ";
      }

      for(int j=i+1-words; j<=i; j++) {
        if(v.at(j).length()==N || (j==i+1-words && length==N)) {
          lines.push_back(v.at(j));
        }
        else lines.at(index) += v.at(j);
        if(j<i) lines.at(index) += " ";
      }
      for(int k=0; k<spaces; k++) {
        lines.at(index) += " ";
      }
      index++;

      full = false;
      length = 0;
      words = 0;
      spaces = 0;
    }
  }
  file.close();

}

void f(vector<string> &lines) {
  int n = lines.size();

  for(int i=0; i<n; i++) {
    cout << lines.at(i) << endl;
  }

}

void r(vector<string> &lines) {
  int n = lines.size();

  for(int i=n-1; i>=0; i--) {
    cout << lines.at(i) << endl;
  }

}

void p(vector<string> &lines, string c2) {
  if(c2=="f"||c2=="null") f(lines);
  else if(c2=="r") r(lines);
}

void k(vector<string> &lines, int kIn) {
  int length = lines.size();
  if(kIn<length && kIn>=0) {
  	cout << lines.at(kIn) << endl;
  }
}

void s(vector<string> &lines, string sIn) {
  vector<string> v;
  int found;

  int n = lines.size();

  for(int i=0; i<n; i++) {
    if(lines.at(i).length()>0) {
      found = lines.at(i).find(sIn,0);
      if(found >= 0 && (found+4==lines.at(i).length()-1 || lines.at(i).at(found+5)==' ')) {
        if(found == 0 || lines.at(i).at(found-1)==' ') {
          v.push_back(lines.at(i));
        }
      }
    }
  }

  for(int i=0; i<v.size(); i++){
    cout << v.at(i) << endl;
  }

}
