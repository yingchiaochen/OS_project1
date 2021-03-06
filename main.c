
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// #include "task.h"
// #include "plist.h"
#include "fifo.h"
#include "rr.h"
#include "sjf.h"
#include "psjf.h"

extern int errno;

// void readFile(char*, tasks_t*);
void readFile(tasks_t*);

const char *sched_policy[] = {
"SCHED_OTHER",
"SCHED_FIFO",
"SCHED_RR",
"SCHED_BATCH"
};



/*
 reminder: I want to use vector to store this reconstruct data now.
 For FIFO and SJF, it just fine.
 For RR, we check it after every time quantum and note that we record the length for delete,
 and using swap to delete completed tasks.
 For SJFP, we use pqueue instead.
 */

int main(int argc, char** argv)
{
    tasks_t taskArr;
    char *sch_type;

    readFile(&taskArr);

    sch_type = taskArr.name;
    // printf("type = %s\n", sch_type);
    // print data
    // for(int i = 0; i < taskArr.num; ++i)
    // {
    //     printf("id = %d\n", taskArr.arr[i].id);
    //     printf("name = %s\n", taskArr.arr[i].name);
    //     printf("rd_time = %d\n", taskArr.arr[i].rd_time);
    //     printf("exe_time = %d\n", taskArr.arr[i].exe_time);
    //     printf("\n");
    // }
 
    // printf("start scheduling!\n");
    if(sch_type[0] == 'F')
    {
        // printf("start %s scheduling\n", "FIFO");
        schedule_fifo(&taskArr);
    }
    else if(sch_type[0] == 'R')
    {
        // printf("start %s scheduling\n", "RR");
        schedule_rr(&taskArr);
    }
    else if(sch_type[0] == 'S')
    {
        // printf("start %s scheduling\n", "SJF");
        schedule_sjf(&taskArr);
    }
    else if(sch_type[0] == 'P')
    {
        // printf("start %s scheduling\n", "PSJF");
        schedule_psjf(&taskArr);
    }
    else
    {

        printf("No type found!\n");
    }
    


    return 0;
}

void readFile(tasks_t* taskArr)
{
    char* temp;
    char buf[100];
    char* name;
    int num, count = 0;
    int rd_time, exe_time;

    // in = fopen(PATH, "r");
    // read head
    fgets(buf, 100, stdin);
    name = strdup(buf);
    name[strlen(name) - 1] = 0;
    taskArr->name = name;
    fgets(buf, 100, stdin);
    num = atoi(buf);    
    taskArr->num = num;


    // printf("name = %s\n", name);
    // printf("num = %d\n", num);
    // printf("\n");

    // initialization
    taskArr->arr = malloc(num * sizeof(task_t));
    taskArr->q = malloc(num * sizeof(task_t));
 
    // read remain data from file
    while (fgets(buf, 100, stdin) != NULL)
    {
        // printf("read data!\n");
        temp = strdup(buf);
        name = strsep(&temp, " ");
        rd_time = atoi(strsep(&temp, " "));
        exe_time = atoi(strsep(&temp, " "));

        // add data into taskArr
        taskArr->arr[count].id = count + 1;
        taskArr->arr[count].name = name;
        taskArr->arr[count].rd_time = rd_time;
        taskArr->arr[count].exe_time = exe_time;
        taskArr->arr[count].rem_time = exe_time;
        taskArr->arr[count].pid = -100;
        pipe(taskArr->arr[count].fd);
         
        count++;
        free(temp);
    }

    // fclose(in);
}

// void readFile(char* path, tasks_t* taskArr)
// {
//     FILE* in;
//     char* temp;
//     char buf[100];
//     char* name;
//     int num, count = 0;
//     int rd_time, exe_time;

//     in = fopen(PATH, "r");
//     // read head
//     fgets(buf, 100, in);
//     name = strdup(buf);
//     name[strlen(name) - 1] = 0;
//     fgets(buf, 100, in);
//     num = atoi(buf);    
//     taskArr->num = num;


//     printf("name = %s\n", name);
//     printf("num = %d\n", num);
//     printf("\n");

//     // initialization
//     taskArr->arr = malloc(num * sizeof(task_t));
//     taskArr->q = malloc(num * sizeof(task_t));
 
//     // read remain data from file
//     while (fgets(buf, 100, in) != NULL)
//     {
//         // printf("read data!\n");
//         temp = strdup(buf);
//         name = strsep(&temp, " ");
//         rd_time = atoi(strsep(&temp, " "));
//         exe_time = atoi(strsep(&temp, " "));

//         // add data into taskArr
//         taskArr->arr[count].id = count + 1;
//         taskArr->arr[count].name = name;
//         taskArr->arr[count].rd_time = rd_time;
//         taskArr->arr[count].exe_time = exe_time;
//         taskArr->arr[count].rem_time = exe_time;
//         taskArr->arr[count].pid = -100;
//         pipe(taskArr->arr[count].fd);
         
//         count++;
//         free(temp);
//     }

//     fclose(in);
// }





