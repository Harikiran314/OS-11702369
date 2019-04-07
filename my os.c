#include<stdio.h> 
#include<conio.h>

void rr(int no,int remaining_time[10],int current_time,int arrival_time[10], int burst_time[10]);

main() 
{
	
        int process_no,j,no,current_time,RemProc,time_quanta,arrival_time[10],burst_time[10],remaining_time[10],x=1;
	int indicator = 0;
	int wait = 0;
	int tut = 0;
	printf("Enter number of processes "); 
	scanf("%d",&no);
	RemProc = no;
	

	printf("\nEnter the arrival time and burst time of the processes\n");
	for(process_no = 0;process_no < no;process_no++) 
	{
		printf("\nProcess P%d\n",process_no+1);
		printf("Arrival time = "); 
		scanf("%d",&arrival_time[process_no]);
		printf("Burst time = "); 
		scanf("%d",&burst_time[process_no]); 
		remaining_time[process_no]=burst_time[process_no]; 
	} 
	printf("The details of time quantum are as follows:\n");
	printf("The time quantum for first round is 3.\n"); 
	time_quanta=3;
	current_time=0;

	for(process_no=0;RemProc!=0;) 
	{

		if(remaining_time[process_no]<=time_quanta && remaining_time[process_no]>0)
		{ 
			current_time+=remaining_time[process_no]; 
			remaining_time[process_no]=0; 
			indicator=1; 
		} 
		else if(remaining_time[process_no]>0)
		{ 
			remaining_time[process_no]-=time_quanta; 
			current_time+=time_quanta; 
		} 
		if(remaining_time[process_no]==0 && indicator==1)			
		{ printf("%d",process_no);
			RemProc--;				
			printf("P %d",process_no+1); 
			printf("\t\t\t%d",current_time-arrival_time[process_no]);
			printf("\t\t\t%d\n",current_time-burst_time[process_no]-arrival_time[process_no]);
			wait+=current_time-arrival_time[process_no]-burst_time[process_no]; 
			tut+=current_time-arrival_time[process_no]; 
			indicator=0; 
                       
		} 
		if(process_no==no-1){
			x++;
			if(x==2){
				process_no=0;
				time_quanta=6;
				
				printf("The time quantum for second round is 6. \n");
			}
			else{
				break;
			}
		}
		else if(current_time >= arrival_time[process_no+1]){
			process_no++;
		}
		else{
			process_no=0;
		}
	}
	
	rr(no,remaining_time,current_time,arrival_time,burst_time);
	
	return 0;
}


void rr(int no,int remaining_time[10],int current_time,int arrival_time[10], int burst_time[10]){
	
	float avg_wait,avg_tut;
    int i,j,n=no,temp,b_time[20],process_no[20],w_time[20],tut_t[20],total=0,loc;
    
    printf("Third round with least burst time.\n");
    
    for(i=0;i<n;i++)
    {
        b_time[i]=remaining_time[i];
        w_time[i]=current_time-arrival_time[i]-b_time[i];
		process_no[i]=i+1;
    }
	
    for(i=0;i<n;i++)
    {
        loc=i;
        for(j=i+1;j<n;j++)
        {
            if(b_time[j]<b_time[loc]){
            	loc=j;
            }
        }
        temp=b_time[i];
        b_time[i]=b_time[loc];
        b_time[loc]=temp;
        temp=process_no[i];
        process_no[i]=process_no[loc];
        process_no[loc]=temp;
    }
	
    for(i=1;i<n;i++)
    {
        for(j=0;j<i;j++){
        	w_time[i]+=b_time[j];
        }
        total+=w_time[i];
    }


 
    avg_wait=(float)total/n;
    total=0;
    printf("\nProcess\t\tBurst time\t\twaiting time\t\tTurnaround Time");
    for(i=0;i<n;i++)
    {
        tut_t[i]=b_time[i]+w_time[i];
        total=total + tut_t[i];
        printf("\nP%d\t\t\t%d\t\t\t%d\t\t\t%d",process_no[i],b_time[i],w_time[i],tut_t[i]);
    }

    avg_tut=(float)total/n;
    printf("\n\nAverage waiting time = %f",avg_wait);
    printf("\n Average turnaround time = %f\n",avg_tut);
	
}



