# AUEP

## Schedule from 2019-07-11

- `2019-12-22` review chapter 11
- `2019-11-26` chapter 11.6.6
- `2019-11-21` chapter 11.5
- `2019-11-20` chapter 11 **Basically review whole chapter in Chinese**
- `2019-11-07` chapter 11 **Use exercises to review this longest chapter 10**
- `2019-11-07` chapter 10.17 **Still need time to understand signal**
- `2019-11-06` chapter 10.16
- `2019-10-29` chapter 10.16 **There will be a lot of coding**
- `2019-10-29` chapter 10.13
- `2019-10-28` chapter 10.6 + review chapter 7.10
- `2019-10-27` review chapter 10 to 10.2.[Program Start-up]
- `2019-10-25` chapter 10.2
- `2019-09-27` chapter 9.1 **Delay reading until finish chapter 10**
- `2019-09-23` chapter 8.14
- `2019-09-23` review chapter 8.4 - 8.12
- `2019-09-14` chapter 8.12
- `2019-09-08` chapter 8.10
- `2019-09-06` chapter 8.4
- `2019-09-01` chapter 8.3
- `2019-08-30` chapter 7.11
- `2019-08-27` chapter 7.9
- `2019-08-19` chapter 7.5
- `2019-08-05` chapter 7.1
- `2019-07-30` chapter 6.1
- `2019-07-29` chapter 5.4
- `2019-07-23` exercise 4.4
- `2019-07-22` chapter 4.19
- `2019-07-22` chapter 4.14
- `2019-07-15` chapter 4.8
- `2019-07-14` exercise 3.4
- `2019-07-13` chapter 3.16
- `2019-07-12` chapter 3.14
- `2019-07-12` chapter 3.12
- `2019-07-11` chapter 3.6
- `2019-07-11` chapter 3.4

## Exercise not solved

- exercise 5.7 [hard]
- exercise 7.4 [can't understand]

## Exervises writed more

- ch07/e7-3.md, "my tipical solution approach".

## Excerpts from the book

- `[f8.17, p255] -> [shell prompt print, p234]`
Note that the shell prints its prompt when the original process
terminates, which is before the second child prints its parent process ID.

-  `[ch8.11, p255] -> [set-user-ID bit, p99]`
When we execute a program file, the effective user ID of the process is usually
the real user ID, and the effective group ID is usually the real group ID.
However, we can also set a special flag in the file's mode word (st_mode) that
says, "When this file is executed, set the effective user ID of the process to
be the owner of the file (st_uid)."
For example, if the owner of the file is the superuser and if the file's
set-user-ID bit is set, then while that program file is running as a process, it
has superuser privileges. This happens regradless of the real user ID of the
process that executes the file. As an example, the UNIX system program that
allows anyone to change his or her password, `passwd`, is a set-user-ID program.
This is required so that the program can write new password to the password file
, typically either `/etc/passwd` or `/etc/shadow`, files that should be writable
only by the superuser. Because a process that is running set-user-ID to some
other user usually assumes extra permissions, it must be written carefully.

- `[ch8.13, p264] put a time-and-date stamp into a certain file`
We could use the functions described in Section 6.10 to do this: call `time` to
get the current calendar time, then call `localtime` to convert it to a
broken-down time, then call `strftime` to format the result, the finally write
the result to the file.

- `[ch8.10, p254] set arg0 in exec functions to be the filename`
Note also that we set the first argument, `argv[0]` in the new prgram, to be the
filename componment of the pathname. Some shell set this argument to be the
complete pathname. This is a convention only; we can set `argv[0]` to any string
we like.

- `[ch11.6, p339] mutex short for mutual-exclusion`
We can protect our data and ensure access by only one thread at a time by using
the pthreads mutual-exclusion interfaces. A **mutex** is basically a lock that
we set (lock) before accessing a shared resource and release (unlick) when we're
done.  

- `[ch11.6, p414] pthread_cond_wait`
The mutex passed to `pthread_cond_wait` protects the condition. The caller
passes it **locked** to the function, which then atomically places the calling
thread on the list of threads waiting for the condition and unlocks the mutex.
This closes the window between the time that the condition is checked and the
time that the thread goes to sleep waiting for the condition to change, so that
the thread doesn't miss a change in the condition. When `pthread_cond_wait`
returns, the mutex is **again locked**.


## Shell command strings
- `kill -l` to show all signals.
- `kill -10 $(ps aux | grep -v grep | grep a.out | awk '{print $2}')` send
SIGUSR1 to process `a.out`.
- `ulimit -a` to show limits, `ulimit -c unlimited` to create a core file when
process core and use `gcc -g` to open debug for gdb.

## Other refereance
- [Opening Streams](
https://www.gnu.org/software/libc/manual/html_node/Opening-Streams.html):
Additional characters may appear after these to specify flags for the call.
Always put the mode
(r, w+, etc) first, that is the only part you are guaranteed will be understood
by all stream. 

