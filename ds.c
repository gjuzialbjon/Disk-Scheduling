#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

void FCFS(int input[][2], int lines){
	//Variables	
	double wait[lines];
	int time = 0;
	int head = 1;
	int oldhead = 1;
	int logical_time = 0;
	double waittime = 0;
	double total = 0;
	double variance[lines];
	double total2 = 0;
	double mean = 0;
	double sd = 0;
	
	for(int i = 0; i < lines; i++){
		//Skip time between a request that has finished and one that has not arrived yet
		if(input[i][0] > logical_time)
			logical_time = input[i][0];	
		
		//Calculate and store wait time
		waittime = logical_time - input[i][0];
		wait[i] = waittime;
		total = total + waittime;
					
		//Move head and increment time units
		oldhead = head;
		head = input[i][1];
		time = time + abs(head - oldhead);
		logical_time = logical_time + abs(head - oldhead);
	}		
	
	mean = total/lines;
	
	for(int i = 0; i < lines; i++) {
		variance[i] = pow(wait[i]-mean,2);	
		total2 = total2 + variance[i];
	}
	
	sd = sqrt(total2/(lines-1));
	printf("FCFS : %4d %12.6lf %12.6lf \n", time, mean, sd);
}

void SSTF(int input[][2], int lines){
	double wait[lines];
	int time = 0;
	int head = 1;
	int oldhead = 1;
	int logical_time = 0;
	double waittime = 0;
	double total = 0;
	double variance[lines];
	double total2 = 0;
	double mean = 0;
	double sd = 0;
	
	int served[lines];
	for(int y = 0; y < lines; y++)
		served[y] = 0;
		
	int k = 0;
	int count = 0;
	
	for(int i = 0; i < lines; i++){
		if(logical_time < input[i][0])
			logical_time = input[i][0];
		
	   count = 0;	
		k = 0;
		while(input[k][0] <= logical_time && k < lines){
			if(served[k] == 0)
				count++;
			k++;
		}
		
		int array[count];
		int arrayIndeces[count];		
		for(int z = 0; z < count; z++){
			array[z] = 0;
			arrayIndeces[z] = 0;
		}
		
		int n = 0;	
		int j = 0;
		//Avoid served or non-arrived requests
		while(n < lines) {
			if(served[n] == 0 && input[n][0] <= logical_time) {
				array[j] = abs(input[n][1] - head);
				arrayIndeces[j] = n;
				j++;	
			}
			n++;
		}
			
		int smallest = 0;		
		for(int m = 1; m < count; m++){
			if(array[m] < array[smallest])
				smallest = m;
		}
		
		//Calculate wait time
		waittime = logical_time - input[arrayIndeces[smallest]][0];
		wait[arrayIndeces[smallest]] = waittime;
		total = total + waittime;
				
		oldhead = head;
		int loc = arrayIndeces[smallest];
		head = input[loc][1];
		served[loc] = 1;
		
		time = time + abs(head - oldhead);
		logical_time = logical_time + abs(head - oldhead);
	}	
	
	mean = total/lines;
	
	for(int i = 0; i < lines; i++) {
		variance[i] = pow(wait[i]-mean,2);	
		total2 = total2 + variance[i];
	}
	
	sd = sqrt(total2/(lines-1));
	
	printf("SSTF : %4d %12.6lf %12.6lf \n", time, mean, sd);
}

void LOOK(int input[][2], int lines){
	//Variables
	double wait[lines];
	int time = 0;
	int head = 1;
	int oldhead = 1;
	int logical_time = 0;
	double waittime = 0;
	double total = 0;
	double variance[lines];
	double total2 = 0;
	double mean = 0;
	double sd = 0;
	
	int served[lines];
	for(int y = 0; y < lines; y++)
		served[y] = 0;

	int k = 0;
	int count = 0;
	int direction = 1;
	int change = 0;

	for(int i = 0; i < lines; i++){
		if(logical_time < input[i][0])
			logical_time = input[i][0];
		
	   count = 0;	
		k = 0;
		while(input[k][0] <= logical_time && k < lines){
			//Based on direction
			if(served[k] == 0) {
				if((input[k][1] - head) >= 0 && direction == 1) {
					count++;
					
				}	
				if((input[k][1] - head <= 0 && direction == -1)) {
					count++;
				}
			}
			k++;
		}
		
		int array[count];
		int arrayIndeces[count];
		
		for(int z = 0; z < count; z++){
			array[z] = 0;
			arrayIndeces[z] = 0;
		}
		
		int n = 0;	
		int j = 0;
		//Avoid served or non-arrived requests
		while(n < lines) {
			if(served[n] == 0 && input[n][0] <= logical_time && direction == 1 && (input[n][1] - head) >= 0) {
				array[j] = abs(input[n][1] - head);
				arrayIndeces[j] = n;
				j++;	
			}
			if(served[n] == 0 && input[n][0] <= logical_time && direction == -1 && (input[n][1] - head) <= 0) {
				array[j] = abs(input[n][1] - head);
				arrayIndeces[j] = n;
				j++;	
			}			
			n++;
		}

		int right = 0;
		int left = 0;		
		if(direction == 1) {
			right = 0;		
			for(int m = 1; m < count; m++){
				if(array[m] < array[right])
					right = m;
			}
		}
		else {
			left = 0;		
			for(int m = 1; m < count; m++){
				if(array[m] < array[left])
					left = m;
			}
		}
		
		int loc = 0;
		
		if(direction == 1) {
			//Calculate wait time
			waittime = abs(logical_time - input[arrayIndeces[right]][0]);
			wait[arrayIndeces[right]] = waittime;
			total = total + waittime;
		
			oldhead = head;
			loc = arrayIndeces[right];
			head = input[loc][1];
			served[loc] = 1;
		
			time = time + abs(head - oldhead);
			logical_time = logical_time + abs(head - oldhead);
		}
		else {
			//Calculate wait time
			waittime = logical_time - input[arrayIndeces[left]][0];
			wait[arrayIndeces[left]] = waittime;
			total = total + waittime;
		
			oldhead = head;
			loc = arrayIndeces[left];
			head = input[loc][1];
			served[loc] = 1;
		
			time = time + abs(head - oldhead);
			logical_time = logical_time + abs(head - oldhead);
		}
		
		int countServed = 0;
		bool dontChange = false;
		int t = 0;
		bool flag = false;	
		for(t=0; t < lines; t++){
			if(served[t] == 0 && input[t][0] <= logical_time) {		
				flag = true;
				if(direction == 1) {
					if(input[t][1] > head) {
						dontChange = true;
						break;
					}
				}
				if(direction == -1) {
					if(input[t][1] < head) {
						dontChange = true;
						break;
					}
				}
			}	
		}

		if(flag == false){
			if(input[i+1][1] >= head && direction == 1)
				dontChange = true;
			if(input[i+1][1] <= head && direction == -1)
				dontChange = true;
		}
		
		if(dontChange == false) {
			if(direction == 1)
				direction = -1;
			else
				direction = 1;
		}	
	}
	
	double total3 = 0;
	for(int i = 0; i < lines; i++) {
		 total3 = total3 + wait[i];
	}
	
	mean = total3/lines;
	
	for(int i = 0; i < lines; i++) {
		variance[i] = pow(wait[i]-mean,2);	
		total2 = total2 + variance[i];
	}
	sd = sqrt(total2/(lines-1));
	
	
	printf("LOOK : %4d %12.6lf %12.6lf \n", time, mean, sd);
}
void CLOOK(int input[][2], int lines){
	//Variables
	double wait[lines];
	int time = 0;
	int head = 1;
	int oldhead = 1;
	int logical_time = 0;
	double waittime = 0;
	double total = 0;
	double variance[lines];
	double total2 = 0;
	double mean = 0;
	double sd = 0;
	
	int served[lines];
	for(int y = 0; y < lines; y++)
		served[y] = 0;

	int k = 0;
	int count = 0;
	int direction = 1;
	int change = 0;

	for(int i = 0; i < lines; i++){
		if(logical_time < input[i][0])
			logical_time = input[i][0];
		
	   count = 0;	
		k = 0;
		while(input[k][0] <= logical_time && k < lines){
			//Based on direction
			if(served[k] == 0) {
				if((input[k][1] - head) >= 0 && direction == 1) {
					count++;
					
				}	
				if((input[k][1] - head <= 0 && direction == -1)) {
					count++;
				}
			}
			k++;
		}
		
		int array[count];
		int arrayIndeces[count];
		
		for(int z = 0; z < count; z++){
			array[z] = 0;
			arrayIndeces[z] = 0;
		}
		
		int n = 0;	
		int j = 0;
		//Avoid served or non-arrived requests
		while(n < lines) {
			if(served[n] == 0 && input[n][0] <= logical_time && direction == 1 && (input[n][1] - head) >= 0) {
				array[j] = abs(input[n][1] - head);
				arrayIndeces[j] = n;
				j++;	
			}
			if(served[n] == 0 && input[n][0] <= logical_time && direction == -1 && (input[n][1] - head) <= 0) {
				array[j] = abs(input[n][1] - head);
				arrayIndeces[j] = n;
				j++;	
			}			
			n++;
		}

		int right = 0;
		int left = 0;		
		if(direction == 1) {
			right = 0;		
			for(int m = 1; m < count; m++){
				if(array[m] < array[right])
					right = m;
			}
		}
		else {
			left = 0;		
			for(int m = 1; m < count; m++){
				if(array[m] > array[left])
					left = m;
			}
		}
		
		int loc = 0;
		
		if(direction == 1) {
			//Calculate wait time
			waittime = abs(logical_time - input[arrayIndeces[right]][0]);
			wait[arrayIndeces[right]] = waittime;
			total = total + waittime;
		
			oldhead = head;
			loc = arrayIndeces[right];
			head = input[loc][1];
			served[loc] = 1;
		
			time = time + abs(head - oldhead);
			logical_time = logical_time + abs(head - oldhead);
		}
		else {
			//Calculate wait time
			waittime = logical_time - input[arrayIndeces[left]][0];
			wait[arrayIndeces[left]] = waittime;
			total = total + waittime;
		
			oldhead = head;
			loc = arrayIndeces[left];
			head = input[loc][1];
			served[loc] = 1;
		
			time = time + abs(head - oldhead);
			logical_time = logical_time + abs(head - oldhead);
		}
		
		int countServed = 0;
		bool dontChange = false;
		int t = 0;
		bool flag = false;	
		for(t=0; t < lines; t++){
			if(served[t] == 0 && input[t][0] <= logical_time) {		
				flag = true;
				if(direction == 1) {
					if(input[t][1] > head) {
						dontChange = true;
						break;
					}
				}
				if(direction == -1) {
					if(input[t][1] < head) {
						dontChange = true;
						break;
					}
				}
			}	
		}
		
		if(flag == false){
			if(input[i+1][1] >= head && direction == 1)
				dontChange = true;
			if(input[i+1][1] <= head && direction == -1)
				dontChange = true;
		}
		
		if(dontChange == false) {
			if(direction == 1)
				direction = -1;
			else
				direction = 1;
		}	
	}
	
	double total3 = 0;
	for(int i = 0; i < lines; i++) {
		 total3 = total3 + wait[i];
	}
	
	mean = total3/lines;
	
	for(int i = 0; i < lines; i++) {
		variance[i] = pow(wait[i]-mean,2);	
		total2 = total2 + variance[i];
	}
	sd = sqrt(total2/(lines-1));
	
	printf("CLOOK: %4d %12.6lf %12.6lf \n", time, mean, sd);
}

int main(int argc, char *argv[])
{
	//Text file
	FILE *file;
	file = fopen(argv[2], "r");

	//If could not open file
	if (!file)
		return 1;

	//Number of requests
	int line_count = 0;
	
	//First iteration to find line number
	int first,second;		
	while(fscanf(file,"%d %d", &first, &second) > 0){
		line_count++;
	}

	//Send pointer back to start of file
	rewind(file);
	
	//Second iteration to store time and cylinders in a line_count X 2 matrix called input
	int inp[line_count][2];
	
	int i = 0;
	while(fscanf(file,"%d %d", &inp[i][0], &inp[i][1]) > 0){
		i++;
	}
	
	//Close the input file
	fclose(file);
	
	//Matrix is ready, we now call the stimulations for the algorithms
	FCFS(inp,line_count);
	SSTF(inp, line_count);
	LOOK(inp,line_count);
	CLOOK(inp,line_count);
	
	return  0;
}



	






