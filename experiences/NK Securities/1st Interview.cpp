char arr[] = "welcome to c+-";
int *p = (int*)arr;
std::cout << (char*)(p+2) << std::endl;
Output for this? to c+-

vector<int> v1;
vector<int> v2(v1);
v2 = v1;

// What will be the output of this code
class A{
     int a;
public:
     A(const A&b) {}
     A& operator=(const A &b) const{
	a = b.a;
	cout << “assignment called” << endl;
      }
};

A a;
A b = a;


// Which implementation is more efficient and why? 

1. 
void multiply_matrices(int in_matrix1[][N], int in_matrix[][N], int result[][N]) 
{ 
    int i, j, k; 
    for (i = 0; i < N; i++) { 
        for (j = 0; j < N; j++) { 
            result[i][j] = 0; 
            for (k = 0; k < N; k++) {
                result[i][j] += in_matrix1[i][k] *  
                             in_matrix[k][j]; 
   
        } 
    } 
}

2. 
void multiply_matrices(int in_matrix1[][N], int in_matrix[][N], int result[][N]) 
{ 
    int i, j, k; 
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) { 
            result[i][j] = 0; 
        }
        for (k = 0; k < N; k++) {
            for (j = 0; j < N; j++) {
                result[i][j] += in_matrix1[i][k] *  
                             in_matrix[k][j]; 
   
        } 
    } 
}


// Suppose you are working on a new project where you are asked to analyze the network latency of incoming UDP packets(incoming rate is in nanoseconds). Below is a part of the pseudocode of the trading system code you need to work on.

Void run_low_latency_loop() {
	Bool completion_status = true;
	While(completion_status) {
		read_packet();
		process_packet();
		perform_trade();
	}
}

// To capture the network latency you need to log the (exchange_timestamp - recv_timestamp) of the packet inside the read_packet() function and store the information in a file for future analysis and reference.

// Assume, you have an efficient LOG function that you will use to log the data in a log_file.

// You make the changes in the code accordingly and you now observe that some of the sequence numbers of packets are missing (i.e there is some packet drop)

// What are the possible reasons for the missing packets?

