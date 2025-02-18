/*
Lets implement a filter function for a firewall, with simple packages.
Packages have an sender ID and a package ID, as well as a 64 byte payload.
Implement a filter function that forward packages from one ringbuffer to another ringbuffer if none
of the configured filters apply.
As a start, filters might drop packages if (a) the sender ID is < 1024, or (b) the package ID is even.
*/

struct Package {
  UUID senderID;
  UUID packageID;
  
  vector<byte> payload(64);
  
  Package(/*Inputs*/) {
      // Initialize the package object.
  }
};

class Rule {
    Rule(const vector<Rule*>& rules): m_rules{rules} {}
    virtual bool validate(const Package& pkg) const {
        for (const Rule* rule: m_rules) {
            if (!rule->validate(pkg)) {
                return false;
            } 
        }
        
        return true;
    }
    
    vector<Rule*> m_rules;
};

class SenderID: Rule {
    bool validate(const Package& pkg) const override {
        return pkg.SenderID >= 1024;
    }
};

class Firewall {
    ringBuffer r1;
    ringBuffer r2;
    Rule rule;
    
    Firewall() /* constructor */
    void Filter() {
        while(!r1.empty()) {
            Package pkg = r1.front();
            r1.pop();
            
            if (rule.validate(pkg)) {
                r2.push(pkg);
            }
        }
    }
};