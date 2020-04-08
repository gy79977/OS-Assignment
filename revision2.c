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
			else if(faculty[ifacultyCount].at > student[istudentCount].at){
				max[maxc]= student[istudentCount];
				maxc++;
				istudentCount++;
			}
			else;
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


}
void main(){
	getinput();
	merging();
	roundRobinAlgo();
}
