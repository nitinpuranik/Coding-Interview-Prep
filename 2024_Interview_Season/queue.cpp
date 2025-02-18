#include <iostream>
#include <vector>
using namespace std;

class Queue {
    private:
        int m_capacity;
        int m_count;
        vector<int> q;
		mutex_t mu;
		cond_t data_available;
		cond_t space_available;

        int m_head, m_tail;
    
    public:
        Queue(int capacity): m_capacity{capacity},
                             m_count{0},
                             q {vector<int>(m_capacity)},
                             m_head{0}, m_tail{0}
        {}

        bool isEmpty() const {
            return m_count == 0;
        }

        bool isFull() const {
            return m_count == m_capacity;
        }

        void push(const int value) {
			mu.lock();
			while(isFull()) {
				cond.wait(&space_available, &mu);
			}

            q[m_tail] = value;
            m_tail = (m_tail + 1) % m_capacity;
            ++m_count;
			
			cond.signal(&data_available);
			mu.unlock();
        }

        int pop() {
			mu.lock();

			while(isEmpty()) {
				cond.wait(&data_available, &mu);
			}
			
            int value = q[m_head];
            m_head = (m_head + 1) % m_capacity;
            --m_count;
			
			cond.signal(&space_available);
			mu.unlock();

            return value;
        }

        void iterate() {
            for (int idx{m_head}, count{m_count}; count > 0;
                    idx=(idx+1)%m_capacity, --count) {
                    cout << q[idx] << ' ';
            }
            cout << "\n";
        }
};

int main() {
    Queue q{5};

    while(true) {
        cout << "Options:\n1: Push\n2: Pop\n3. Print\n4. Quit\n\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                if (q.isFull()) {
                    cout << "Queue is full. Please retry...\n\n";
                    continue;
                }
                
                int value;
                cout << "Enter value to push: ";
                cin >> value;

                q.push(value);
                cout << "Successfully pushed " << value << "\n\n";
                break;
            
            case 2:
                if (q.isEmpty()) {
                    cout << "Queue is empty. Please retry...\n\n";
                    continue;
                }

                cout << "Value popped: " << q.pop() << "\n\n";
                break;
            
            case 3:
                if (q.isEmpty()) {
                    cout << "Queue is empty. Please retry...\n\n";
                    continue;
                }

                cout << "Queue items: ";
                q.iterate();
                cout << "\n";
                break;

            case 4:
                cout << "Ending program. Bye!\n";
                return 0;
            
            default:
                cout << "Invalid choice. Please retry...\n\n";
        }
    }

    return 0;
}