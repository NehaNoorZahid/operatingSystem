def run_fifo_scheduling():
    print("\n*~~~~~*~~~~~*~~~~~*~~~~~*~~~~~*~~~~~*~~~~~*~~~~~*~~~~~*~~~~~*~~~~~*")
    print("                    FIFO Scheduling Algorithm                        ")
    print("*~~~~~*~~~~~*~~~~~*~~~~~*~~~~~*~~~~~*~~~~~*~~~~~*~~~~~*~~~~~*~~~~~*\n")

    print(
        "Instruction: Please enter a number for the following: \n"
        + "\n\t*Number of Processes (with min. of 5 and max. of 10) \n"
        + "\t*Burst time (with min. of 5 and max. of 15 each) \n"
        + "\t*Arrival time (with min. of 1 and max. of 12 each) \n"
    )

    pid = []
    while True:
        try:
            n = int(input("Number of Processes: "))
            if 5 <= n <= 10:
                for j in range(1, n + 1):
                    pid.append(f"P{j}")
                break
            else:
                print("\n'Invalid input. Please enter number 5 to 10 only.'\n")
        except ValueError:
            print("\n'Invalid input. Please enter an integer.'\n")

    burst_time = [0] * (n + 1)
    arrival_time = [0] * (n + 1)
    completion_time = [0] * (n + 1)
    turnaround_time = [0] * (n + 1)
    waiting_time = [0] * (n + 1)

    for h in range(1, n + 1):
        while True:
            burst_time[h] = input(f'Burst Time of "{pid[h-1]}": ')
            if burst_time[h].isnumeric():
                burst_time[h] = int(burst_time[h])
                if 5 <= burst_time[h] <= 15:
                    break
                else:
                    print("'Invalid input. Please enter from 5 to 15 only.'")
            else:
                print("'Invalid input. Please enter an integer.'")

        while True:
            arrival_time[h] = input(f'Arrival Time of "{pid[h-1]}": ')
            if arrival_time[h].isnumeric():
                arrival_time[h] = int(arrival_time[h])
                if 1 <= arrival_time[h] <= 12:
                    break
                else:
                    print("'Invalid input. Please enter from number 1 to 12 only.'")
            else:
                print("'Invalid input. Please enter an integer.'")

    # Initializing variables for scheduling
    total_turnaround_time = 0
    total_waiting_time = 0
    current_time = 0

    gantt_pid = []
    gantt_completion_times = []

    for i in range(1, n + 1):
        # If CPU is idle, move current time to the arrival time of the next process
        if current_time < arrival_time[i]:
            current_time = arrival_time[i]

        completion_time[i] = current_time + burst_time[i]
        turnaround_time[i] = completion_time[i] - arrival_time[i]
        waiting_time[i] = turnaround_time[i] - burst_time[i]

        total_turnaround_time += turnaround_time[i]
        total_waiting_time += waiting_time[i]

        gantt_pid.append(pid[i-1])
        gantt_completion_times.append(completion_time[i])
        current_time += burst_time[i]

    avg_turnaround_time = total_turnaround_time / n
    avg_waiting_time = total_waiting_time / n

    print("\nTable:")
    print("   ————————————————————————————————————————————————————————")
    print("  | Process | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time |")
    print("   ————————————————————————————————————————————————————————")
    for i in range(1, n + 1):
        print(f"  | {pid[i-1]:<8} | {arrival_time[i]:<12} | {burst_time[i]:<10} | {completion_time[i]:<15} | {turnaround_time[i]:<15} | {waiting_time[i]:<12} |")
    print("   ————————————————————————————————————————————————————————")

    print("\nAverage Waiting Time (AWT):", round(avg_waiting_time, 2), "ms")
    print("Average Turnaround Time (ATT):", round(avg_turnaround_time, 2), "ms")

    # Display Gantt Chart
    print("\nGantt Chart:\n")
    for pid in gantt_pid:
        print(f" {pid} ", end="")
    print()

    print("|", end="")
    for _ in gantt_pid:
        print("----", end="")
    print("|")

    print(f"{arrival_time[1]:<4}", end="")  # Start with the arrival time of the first process
    for time in gantt_completion_times:
        print(f"{time:<4}", end="")  # Print each completion time
    print()
