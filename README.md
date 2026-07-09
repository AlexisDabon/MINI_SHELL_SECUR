# README - SENTRY-sh 🛡️

A minimalist security-focused mini-shell designed to isolate process execution, enforce command whitelisting, and run real-time auditing.

---

## Objectives

Simulate a hardened environment guardrail. The program monitors user inputs in a continuous loop: if an unauthorized command or system disruption is detected, the shell blocks the execution, logs the intrusion attempt, and protects the parent terminal.

---

## 1. The C Part

Robust POSIX low-level programming featuring input sanitization, custom signal management (`SIGINT` interception), persistent logging automation, and strict error handling during process creation.

---

## 2. The Shell Guardrail

It handles process isolation seamlessly by preventing execution from leaking outside the designated scope. It catches execution states on the fly and acts as a firewall between the user input and the operating system noyau.

---

## Architecture States

* **Allowed Execution** -> Command matches the whitelist, a child process is isolated via `fork()` and executed via `execlp()`.
* **Security Exception** -> Command is rejected, access is denied, and the event is instantly appended to the audit trail.
* **Resilience Mode** -> `Ctrl+C` (`SIGINT`) signals are caught and ignored, preventing unexpected environment termination.

---

<details>
<summary>📜 <b>Project Specifications & Phases</b></summary>

### [1] Core Shell Architecture
- Continuous execution loop printing the custom `[SENTRY-sh]$` prompt.
- Clean input capturing using `fgets` to prevent typical string overflow issues.

### [2] Input Sanitization & Parsing
- Systematic removal of trailing newline characters (`\n`) to ensure accurate command parsing.
- Interception of internal commands (e.g., `exit`) to ensure a clean session closing sequence.

### [3] Whitelist Enforcement (Guardrail)
- Fixed static list of trusted system commands (`ls`, `pwd`, `clean`, `date`, `exit`).
- Strict iteration loop comparing inputs against the whitelist before any execution right is granted.

### [4] Auditing & Logging Pipeline
- Automated file stream handling with `fopen()` in append mode (`"a"`).
- Real-time logging of unauthorized attempts formatted with custom timestamped `[ALERTE SECURITY]` flags into `sentry.log`.

### [5] Process Isolation & Signaling
- Safe execution design utilizing `fork()` to create an isolated child process space.
- Context execution transition using `execlp()`, with immediate `exit(127)` protection if the command fails.
- Complete immunization against `SIGINT` using `signal(SIGINT, SIG_IGN)`.
</details>
