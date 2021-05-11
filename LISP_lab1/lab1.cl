;1
(defconstant iterDots 5)
;2
(defconstant recDots 5)
;3
(defconstant aList '(b a c b a (a a a v) a b (a) b))
;4
(defconstant fibNum 9)
;5
(defconstant a 10)
(defconstant b 5)
;6
(defconstant sum 7)


(defun iterPrintDots (n)
    (loop
        (setq n (- n 1))
        (princ ".")
        (when (<= n 0) (return))
    )
    (terpri) ;terminate printing
)

(defun recPrintDots (n)
    (setq n (- n 1))
    (if (>= n 0) 
        (progn      ;then
            (princ ".")
            (recPrintDots n)
        )
        (terpri)    ;else
    )
)

(defun recCountA (list)
    (cond
        ((null list) 0) ;empty list return 0
        ((listp (car list)) (recCountA (cdr list))) ;sub-list found, move on
        ((string-equal "A" (car list)) (1+ (recCountA (cdr list)))) ;found 'A', add to count and move on
        (t (recCountA (cdr list)))  ;'A' not found, move on
    )
)

(defun fib (n)
    (cond
        ((= n 0) 0) ;base cases
        ((= n 1) 1)
        (t (+ (fib (- n 1)) (fib (- n 2)))) ;get next fib number
    )
)

(defun findMax (n1 n2)
    (if (> n1 n2) 
        n1  ;then return n1
        n2  ;else return n2
    )
)

(defun summation (n)
    (cond
        ((< n 1) 0) ;base case
        ((>= n 1) (+ n (summation (- n 1))))    ;add to count and move on
    )
)

(defun test ()
    (format t "CMPS 3500 Lab01 Name: Nicholas Jordan~%")
    
    (format t "01. Printing ~D dots iteratively: " iterDots) (iterPrintDots iterDots)

    (format t "02. Printing ~D dots recursively: " recDots) (recPrintDots recDots)

    (format t "03. There are ~D A's in list: " (recCountA aList)) (princ aList) (terpri)

    (format t "04. Fibonacci #~D: ~D~%" fibNum (fib fibNum))

    (format t "05. Max between ~D and ~D: ~D~%" a b (findMax a b))

    (format t "06. Summation of 1 to ~D: ~D~%" sum (summation sum))
)

(test)

