#include <stdio.h>
#include <stdlib.h>
#include <cstring>

typedef struct Process {
    char pid[3];            // Process ID
    int arrival_time;        // Arrival time
    int exe_time;            // Total execution time
    int remaining_time;      // Remaining execution time
    int resource_info_flag;  // Resource information flag (0 or 1)
    char state[10];          // Process state (initially Running)
    int ir;                  // Next instruction address (quantum address)
    int* execution_array;     // Execution time as an array
} Process;

// output printing code
void display_pcb(Process *process, char* next_process) {
    // Display PCB info
    printf("\n--- Process Control Block for %s ---\n", process->pid);
    printf("| Process ID:          %s\n", process->pid);
    printf("| IR (Next Quantum):   %d\n", process->ir);
    printf("| PC (Next Process):   %s\n", next_process);
    printf("| Arrival Time:        %d\n", process->arrival_time);
    printf("| Execution Time:      %d\n", process->exe_time);
    printf("| State:              %s\n", process->state);
    printf("| Resource Access:     %s\n", process->resource_info_flag ? "Yes" : "No");

    // Show the resume instruction and address
    if (process->ir < process->exe_time) {
        int next_ir = (process->ir + 1 < process->exe_time) ? process->ir + 1 : process->exe_time;
        int resume_value = process->execution_array[process->ir];
        printf("| PSW: Resume Instruction Value = Value %d, Resume Instruction Address = Index %d\n", resume_value, process->ir);
    } else {
        printf("| PSW: Process finished execution\n");
    }
    printf("----------------------------------------\n");
}

void round_robin(Process processes[], int quantum, int n) {
    int time = 0;
    int completed_processes = 0;

    while (completed_processes < n) {
        for (int i = 0; i < n; i++) {
            Process *process = &processes[i];
            
            if (process->remaining_time > 0) {
                char* next_process = processes[(i + 1) % n].pid;  // Get next process ID
                
                // Run process for one quantum
                printf("Time %d: Running Process %s\n", time, process->pid);
                
                for (int j = 0; j < quantum; j++) {
                    if (process->remaining_time > 0) {
                        process->ir += 1;  // Increment IR for each time unit
                        process->remaining_time -= 1;  // Reduce remaining time
                        time++;
                    }
                }

                // Display PCB after each quantum execution
                display_pcb(process, next_process);
                
                if (process->remaining_time == 0) {
                    strcpy(process->state, "Exit");
                    completed_processes++;
                }
            }
        }
    }

    printf("All processes are complete.\n");
}

int main() {
    int quantum = 2;
    int n;

    printf("Enter number of processes (limit 5): ");
    scanf("%d", &n);
    Process processes[n];

    for (int i = 0; i < n; i++) {
        char pid[3];
        sprintf(pid, "P%d", i + 1);
        
        printf("Enter arrival time for %s: ", pid);
        int arrival_time;
        scanf("%d", &arrival_time);
        
        printf("Enter execution time for %s (limit 10): ", pid);
        int exe_time;
        scanf("%d", &exe_time);
        
        printf("Enter resource information flag (0 or 1) for %s: ", pid);
        int resource_info_flag;
        scanf("%d", &resource_info_flag);

        processes[i].arrival_time = arrival_time;
        processes[i].exe_time = exe_time;
        processes[i].remaining_time = exe_time;
        processes[i].resource_info_flag = resource_info_flag;
        strcpy(processes[i].pid, pid);
        strcpy(processes[i].state, "Running");
        processes[i].ir = 0;
        processes[i].execution_array = (int*)malloc(exe_time * sizeof(int));

        // Fill the execution array
        for (int j = 0; j < exe_time; j++) {
            processes[i].execution_array[j] = j + 1;
        }
    }

    // Display the initial PCB table
    printf("\n--- Initial PCB Table ---\n");
    printf("| %-10s | %-15s | %-15s | %-15s |\n", "Process", "Arrival Time", "Execution Time", "Resource Info");
    printf("|------------|----------------|----------------|----------------|\n");
    for (int i = 0; i < n; i++) {
        printf("| %-10s | %-15d | %-15d | %-15d |\n", processes[i].pid, processes[i].arrival_time, processes[i].exe_time, processes[i].resource_info_flag);
    }
    printf("----------------------------------------\n");

    printf("\nStarting Round-Robin Scheduling...\n\n");
    round_robin(processes, quantum, n);

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(processes[i].execution_array);
    }

    return 0;
}
