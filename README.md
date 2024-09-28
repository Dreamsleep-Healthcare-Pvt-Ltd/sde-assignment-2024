# sde-assignment-2024
Fork this repository and push your code

## Assignment Questions

Design a system application to implement opening of different types of bank accounts. The fields could be accountNumber, account type, accountHolderName, age, branch, balance, interestRate, accountOpeningDate. Some accounts will also have fixed deposit linked to it. In that case, the account shall also contain the information for FD: fdOpeningDate, fdMaturityDate, fdInterestRate, isSeniorCitizen
Based on the type of account there will be a quarterly interestRate credited SAVINGS: 4%, CURRENT: 0%
Based on the tenure of the FD, the interest rate will be: 0-3 years: 7% 3-5 years: 7.2% 5-10 years: 7.5% 10-12 years: 7.9%
If the owner is a senior citizen, then they will also be eligible for extra 0.25% for their FD and if the owner is a female they will be eligible for added 0.1% on FD interest rate.

Design a system application to implement a library management system where users can search for books, borrow them, and return them. The system should hide the complexity of searching, borrowing, and updating the inventory of books.

Design a microservice in Go, which can be used as an authenticator backend for single sign on. The tasks for this assignment would be: a. Setting up SSO (Single sign-on) with Google/Apple b. Design a barebones frontend for facilitating this c. Design the Go backend.
Read about OAuth 2.0 and why this backend is required.
