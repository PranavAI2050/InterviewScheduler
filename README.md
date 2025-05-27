# Interview Scheduler

This project implements an **automated interview scheduling system** for students and companies, based on their availability, number of interview rounds, panel limitations, and required time slots.

## 🚀 Deliverables

* ✅ Working C++ code with proper input/output handling
* 📄 Documentation explaining algorithmic approach
* ⏱ Time complexity analysis
* 🧪 Sample test cases and outputs

---

## 🧠 Algorithm Choice

The scheduler prioritizes students using a **min-heap (priority queue)** based on their current availability time (`currentTime`). The system iteratively schedules the earliest possible interview for each student, considering:

* Company’s `currentTime` (earliest when a panel is available)
* Number of `rounds` per company
* Number of available `panels`
* Duration per round

The company with the earliest available slot is selected next. The student and company time pointers are updated dynamically.

---

## ⏱ Time Complexity Analysis

Let:

* `S` = number of students
* `C` = number of companies
* `R` = max rounds per company

**Time Complexity:**

* Heap operations per round per student: `O(log S)`
* Total iterations: up to `S * C * R`
* **Total Time Complexity:** `O(S * C * R * log S)`

---

## 📥 Sample Input / Output

### ✅ Sample 1

**Input:**

```
9 17
Google
3
2
1
Microsoft
2
1
1.5
Amazon
2
2
2
stop
A1
Google
Microsoft
done
A2
Amazon
Google
done
A3
Microsoft
done
stop
```

**Output:**

```
Student: A1
Company  Round  Start  End   Panel
Google    1      9:00   9:01   1
Google    2      9:01   9:02   2
Google    3      9:02   9:03   1
Microsoft 1      9:03   9:04   1
Microsoft 2      9:04   9:06   1

Student: A2
Company  Round  Start  End   Panel
Amazon    1      9:00   9:02   1
Amazon    2      9:02   9:04   2
Google    1      9:04   9:05   2
Google    2      9:05   9:06   1
Google    3      9:06   9:07   2

Student: A3
Company  Round  Start  End   Panel
Microsoft 1      9:00   9:01   1
Microsoft 2      9:01   9:03   1
```

---

### ✅ Sample 2

**Input:**

```
9 12
A
2
2
30
B
1
1
45
stop
S1
A
B
done
S2
A
done
S3
B
done
stop
```

**Output:**

```
Student: S1
Company  Round  Start  End   Panel
A         1      9:00   9:30   1
A         2      9:30  10:00   1
B         1     10:00  10:45   1

Student: S2
Company  Round  Start  End   Panel
A         1      9:00   9:30   2
A         2      9:30  10:00   2

Student: S3
Company  Round  Start  End   Panel
B         1      9:00   9:45   1
```

---

### ❌ Conflict Case

**Input:**

```
9 11
A
1
1
60
B
1
1
60
C
1
1
60
stop
S1
A
B
C
done 
stop
```

**Output:**

```
The interviews cannot be scheduled with the given requirements
```

---

## 🛠 How to Run

This code is written in standard C++. To compile and run:

```bash
g++ -o interview.exe interview.cpp
./interview
```

---

## 📌 Notes

* Time is taken in 24-hour format and converted to minutes internally.
* Supports dynamic input for companies and students.
* Handles edge cases like time overflow and panel shortages.

---

## ✍️ Author

**Pranav Atote**
Third-year B.Tech Aerospace Engineering, IIT Bombay
Email: [atotepranavdipak@gmail.com](mailto:atotepranavdipak@gmail.com)

