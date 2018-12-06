#include <signal.h>
//Немного полезных функций.

int sigprocmask(int how, const sigset_t *set, sigset_t *old_set);
int sigempty(sigset_t *set);
int sigfillset(sigset_t *set);
int sigaddset(sigset_t *set, int signo);
int sigdelset(sigset_t *set, int signo);
int sigismember(const sigset_t *set, int signo);
int sigpending(sigset_t *set);
int sigaction(int sig, const struct sigaction *restrict ect, struct sigaction *restrict oact);
struct sig_action {
    void (*sa_handler) (int);
    void (sa_sigaction) (int, siginfo_t *, void *);
    sigset_t sa_mask;
    int sa_flags;
};
