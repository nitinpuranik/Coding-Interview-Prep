#include <iostream>
#include <vector>
using namespace std;

class Solution {
private:
    void Print (const string& str, long sum, char sign, long num, int target,
                vector<string>& vexp, string& exp) {
      static unsigned idx = 1;

      if (idx == str.length()) {
        if (exp != str && sum == target) {
          cout << "Debug: sum = " << sum << ", target = " << target << endl;
          cout << exp << endl;
          vexp.push_back(exp);
        }
        return;
      }

      long tsum = sum;
      char tsign = sign;
      long tnum = num;  

      for (long i = 0; i < 4; i++) {

        switch (i) {

          case 0:
            if (tnum == 0)
              continue;

            if (tsign == 'x') {
              tsum = tsum * 10 + str[idx] - '0';
              tnum = tsum;
            }

            else if (tsign == '+') {
              tsum = tsum - tnum;

              tnum = tnum * 10 + str[idx] - '0';
              tsum += tnum;
            }

            else if (tsign == '-') {
              tsum = tsum + tnum;

              tnum = tnum * 10 + str[idx] - '0';
              tsum -= tnum;
            }

            else if (tsign == '*') {
              if (tnum > 0)
                tsum = tsum / tnum;

              tnum = tnum * 10 + str[idx] - '0';
              tsum *= tnum;
            }
            break;

          case 1:
            tsum += str[idx] - '0';
            tnum = str[idx] - '0';
            tsign = '+';
            exp += "+";
            break;

          case 2:
            tsum -= str[idx] - '0';
            tnum = str[idx] - '0';
            tsign = '-';
            exp += "-";
            break;

          case 3:
            if (tsign == '+') {
              tsum -= tnum;
              tnum *= (str[idx] - '0');
              tsum += tnum;
            }

            else if (tsign == '-') {
              tsum += tnum;
              tnum *= (str[idx] - '0');
              tsum -= tnum;
            }

            else {
              tsum *= (str[idx] - '0');
              tnum = str[idx] - '0';
            }

            exp += "*";
            break;
        }

        exp += str.substr(idx, 1);

        idx++;
        Print (str, tsum, tsign, tnum, target, vexp, exp);

        idx--;
        exp.pop_back();

        if (i > 0)
          exp.pop_back();

        tsum = sum;
        tsign = sign;
        tnum = num;
      }
}
public:
    vector<string> addOperators(string num, int target) {
        if (num.length() < 2)
            return vector<string>();
        
        string exp {num[0]};
        vector<string> vexp;
        
        Print(num, num[0] - '0', 'x', num[0] - '0', target, vexp, exp);
        
        return vexp;
    }
};

int main() {
  string num = "1234";
  
  vector<string> vexp = Solution().addOperators (num, 9191);
  
  //for (const string& exp : vexp)
    //cout << exp << endl;
  return 0;
}