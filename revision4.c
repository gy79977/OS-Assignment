#include<stdio.h>
#include<unistd.h>
struct job{
	int processId;
	int at;
	int bursttime;
	int completiontm;
	int remainingbt;
}faculty[100], student[100], max[100];

int n, facultyCount=0, studentCount=0, maxc=0;
int quantum;

void roundRobinAlgo(){
	int time= max[0].at, mark=0, cct=0, i, rc;
	while(time!=120 && cct!=maxc){
		for(i=0; i<=mark; i++){
			if(max[i].remainingbt > quantum){
				time += quantum;
				max[i].remainingbt -= quantum;
			}
			else if(max[i].remainingbt <=quantum && max[i].remainingbt !=0){
				time += max[i].remainingbt;
				max[i].remainingbt =0;
				max[i].completiontm = time;
				cct++;
			}
			else;
		}
		int start = mark+1;
		for(rc= start; rc<maxc; rc++){
			if(max[rc].at <= time){
				mark++;
			}
		}
	}	
}

void merging(){
	int istudentCount=0, ifacultyCount= 0, min, flag;
	if( facultyCount!=0  && studentCount!=0){
		while(istudentCount<studentCount && ifacultyCount<facultyCount){
			if(faculty[ifacultyCount].at == student[istudentCount].at){
				max[maxc] = faculty[ifacultyCount];
				maxc++;
				ifacultyCount++;
				max[maxc]= student[istudentCount];
				maxc++;
				istudentCount++;
			}
			else if(faculty[ifacultyCount].at < student[istudentCount].at){
				max[maxc]= faculty[ifacultyCount];
				maxc++;
				ifacultyCount++;
			}
			else if(faculty[ifacultyCount].at > student[istudentCount].at){
				max[maxc]= student[istudentCount];
				maxc++;
				istudentCount++;
			}
			else;
		}
		if(maxc != (facultyCount+studentCount)){
			if(facultyCount!=ifacultyCount){
				while(ifacultyCount!=facultyCount){
					max[maxc]= faculty[ifacultyCount];
					maxc++;
					ifacultyCount++;
				}
			}
			else if(studentCount!=istudentCount){
				while(istudentCount!=studentCount){
					max[maxc]= student[istudentCount];
					maxc++;
					istudentCount++;
				}
			}
		}
	}
	else if(facultyCount==0){
		while(istudentCount!=studentCount){
			max[maxc]= student[istudentCount];
			maxc++;
			istudentCount++;
		}
	}
	else if(studentCount==0){
		while(ifacultyCount!=facultyCount){
			max[maxc]= faculty[ifacultyCount];
			maxc++;
			ifacultyCount++;
		}
	}
	else {
		printf("\n There are no valid Jobs found.n");
	}
}

void output(){
	int j=0, total=0, sum=0; 
	double average;
	printf("\nHere is the Execution\n");
	printf("\nQuery ID\tArrival Time\tCPU Burst Time\tCompletion Time\tTurn Around Time\tWaiting Time");
	for(j; j<maxc; j++){
		printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d",
		max[j].processId, (max[j].at+1000), max[j].bursttime, (max[j].completiontm+1000), (max[j].completiontm-max[j].at), ((max[j].completiontm-max[j].at)- max[j].bursttime));
		total= max[j].completiontm;
		sum+= (max[j].completiontm-max[j].at);
	}
	average = sum/maxc;
	printf("\n\nTotal time Spent for all queries: %d", total);
	printf("\nAverage time for queries: %lf", average);
	printf("\nProcess execution has completed");
}

void getinput(){
	int mapping, i, arrivtime;
	printf("Enter total number of queries: "); scanf("%d", &n);
	if(n==0) { printf("\n No queries entered\n"); }
	else{
		printf("\nEnter Time Quantum for round robin: "); scanf("%d", &quantum);
		printf("\nEnter 1 for Faculty and 2 for Student\n");
		for(i=0; i<n; i++){
			printf("\nJob Type (1/2): "); scanf("%d", &mapping);
			if(mapping==1){
				printf("Enter Query Id: "); scanf("%d", &faculty[facultyCount].processId);
				printf("Enter Arrival Time in terms of 2400 hrs "); scanf("%d", &arrivtime);
				if(arrivtime<1000 || arrivtime>1200){
					printf("\nEnter Correct time");
					getinput();
				}
				else{faculty[facultyCount].at= arrivtime-1000;}
				printf("Enter CPU Burst Time: "); scanf("%d", &faculty[facultyCount].bursttime);	 faculty[facultyCount].remainingbt= faculty[facultyCount].bursttime; 
				facultyCount++;
			} else{
				printf("Enter Query Id: "); scanf("%d", &student[studentCount].processId);
				printf("Enter Arrival Time: "); scanf("%d", &arrivtime); 
				if(arrivtime<1000 || arrivtime>1200){
					printf("\nEnter Correct time\n");
					getinput();
				}
				else {student[studentCount].at= arrivtime-1000; }
				printf("Enter CPU Burst Time: "); scanf("%d", &student[studentCount].bursttime);	 student[studentCount].remainingbt= student[studentCount].bursttime;
				studentCount++;
			}
		}
	}
}

void instruction(){
	printf("\nHey ! Welcome, Please follow following instruction for proper functioning of the code"
			"\n**>Enter time in 2400 hours format. Like for 11:30 am enter 1130"
			"\n**>Enter Queries arrival times in ascending order, i.e. In real time arrival manner\n"
			"\nAll Time units are in 'Minutes'. \n\n"
			);
}
void main(){
 	instruction();
	getinput();
	merging();
	roundRobinAlgo();
	output();
}
