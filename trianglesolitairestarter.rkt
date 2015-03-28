;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname trianglesolitairestarter) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ())))

;; triangle-solitaire-starter.rkt



;; ===========================================
;; ===========================================
;; Position is Natural[0, 14]
;; interp. 0 based indexes into a board

(define-struct jump (from over to))
;; Jump is (make-jump Position Position Position)
;; interp.
;;  a jump on the board, with the from, to and
;;  jumped over positions
;; All the potential jumps on a board. Given these jumps, at
;; any given time the possible next moves are just the subset
;; of these jumps that are valid.

;; Board is (listof Boolean)
;; interp. false is an occupied position, 
;;         true is an empty position

(define-struct pair (board jump))
;; Pair is (make-pair Board Jump)
;; interp. a board and a jump that has been applied to it

;; ===========================================
;; ===========================================
;; Constants:

(define F false)
(define T true)

(define POSITIONS
  ;; (list         0
  ;;              1 2
  ;;            3  4  5
  ;;          6  7  8  9
  ;;        10 11 12 13 14))
  (list 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14))


(define JUMPS
  (list (make-jump  0 1  3) (make-jump  0  2  5)
        (make-jump  1 3  6) (make-jump  1  4  8)
        (make-jump  2 4  7) (make-jump  2  5  9)
        (make-jump  3 1  0) (make-jump  3  4  5) (make-jump  3  6 10) (make-jump  3  7 12)
        (make-jump  4 7 11) (make-jump  4  8 13)
        (make-jump  5 2  0) (make-jump  5  4  3) (make-jump  5  8 12) (make-jump  5  9 14)
        (make-jump  6 3  1) (make-jump  6  7  8)
        (make-jump  7 4  2) (make-jump  7  8  9)
        (make-jump  8 4  1) (make-jump  8  7  6)
        (make-jump  9 5  2) (make-jump  9  8  7)
        (make-jump 10 6  3) (make-jump 10 11 12)
        (make-jump 11 7  4) (make-jump 11 12 13)
        (make-jump 12 7  3) (make-jump 12  8  5) (make-jump 12 11 10) (make-jump 12 13 14)
        (make-jump 13 8  4) (make-jump 13 12 11)
        (make-jump 14 9  5) (make-jump 14 13 12)))

(define J0 (make-jump 0 0 0))    ;invalid jump, for tests only/base case !!!!!
(define J1 (make-jump 5 2 0))
(define J2 (make-jump 3 1 0))
(define J3 (make-jump 2 5 9))


(define B0  
  (list     T
          F  F
        F  F  F
       F F  F  F
     F F  F  F  F))

(define B0s 
  (list     F
          T  T
        T  T  T
       T T  T  T
     T T  T  T  T))

(define B01  
  (list     F
          F  T
        F  F  T
       F F  F  F
     F F  F  F  F))

(define B001  
  (list     F
          F  T
        F  F  F
       F F  F  T
     F F  F  F  T))

(define B02  
  (list     F
          T  F
        T  F  F
       F F  F  F
     F F  F  F  F))

(define B1 
  (list     F
          F  T
        F  F  F
       F F  T  F
     F F  T  F  F))

(define B2
    (list    F
           F  F
         F  T  F
       F F  F  F
      F F  F  F  F))

(define B3 
  (list     T
          T  F
        T  T  F
       T T  T  T
     T T  T  T  T))

(define B4 
  (list     T
          T  T
        T  T  T
       T T  T  F
     T T  T  T  T))

(define B5 
  (list     F
          F  F
        F  F  T
       F F  T  T
     F F  T  F  F))

(define B6 
  (list     F
          F  F
        F  T  F
       F T  T  F
     F F  T  F  F))

(define B7 
  (list     F
          T  T
        F  T  F
       F F  F  F
     F F  T  F  F))

(define B8 
  (list     F
          F  T
        F  F  F
       T T  F  F
     F F  T  F  F))

(define B9 
  (list     F
          F  T
        T  F  F
       F T  T  F
     F F  F  F  F))

(define B10  
  (list     F
          F  T
        F  F  F
       F F  T  F
     F F  F  T  T))

(define B11 
  (list     F
          F  T
        F  F  F
       F F  T  F
     T T  F  F  F))

(define B12 
  (list     T
          T  F
        F  F  T
       T T  T  T
     T T  T  T  T))

;; ===========================================
;; ===========================================
;; Functions:

;; ==============
;; Board -> (listof Jump)
;; produce a solution for bd; or false if bd is unsolvable
;; Assume: bd is valid 

(check-expect (solve B0)
              (list
               (make-jump 3 1 0)
               (make-jump 5 4 3)
               (make-jump 0 2 5)
               (make-jump 6 3 1)
               (make-jump 9 5 2)
               (make-jump 11 7 4)
               (make-jump 12 8 5)
               (make-jump 1 4 8)
               (make-jump 2 5 9)
               (make-jump 14 9 5)
               (make-jump 5 8 12)
               (make-jump 13 12 11)
               (make-jump 10 11 12)))
                    

;(define (solve bd) JUMPS)  ;stub

(define (solve bd)
  (local [(define (solve--p p)
            ;; Pair -> (listof Pair)                                          !!!
            (if (solved? p)
                empty
                (solve--lop (next-boards p))))
          (define (solve--lop lop)
            ;; (listof Pair) -> (listof Pair)
            (cond [(empty? lop) false]   
                  [else
                   (local [(define try (solve--p (first lop)))]
                     (if (false? try)
                         (solve--lop (rest lop))
                         (cons (first lop)
                               try)))]))]
    (produce-steps (cons (make-pair bd J0)
                         (solve--p (make-pair bd J0))))))

;; ============== 
;; Pair -> Boolean
;; produce true if the board is solved 
;;   i.e., all but one position is occupied
(check-expect (solved? (make-pair B0 J0)) false)
(check-expect (solved? (make-pair B0s J0)) true) 
(check-expect (solved? (make-pair B1 J0)) false)
(check-expect (solved? (make-pair B3 J0)) false)

;(define (solved? bd) true)  ;stub
 
(define (solved? p)
  (local [(define (count-false bd)
            ;; Board -> Natural
            (cond [(empty? bd) 0] 
                  [else
                   (if (false? (first bd)) 
                       (+ 1 (count-false (rest bd)))
                       (count-false (rest bd)))]))]
    (= 1 (count-false (pair-board p)))))
 
;; ==============
;; Pair -> (listof Pair)
;; filter all jump options to find the valid ones;
;;    then apply the valid jumps to the board to produce a list of pairs
;; ASSUME: The consumed board is valid
(check-expect (next-boards (make-pair B3 J0))(list (make-pair B4 J3)
                                    (make-pair B0s J1)))
(check-expect (next-boards (make-pair B0 J0))(list (make-pair B02 J2)
                                    (make-pair B01 J1)))
;(check-expect (next-boards B1)(list B7 B9 B8 B6 B5 B11 B10))                 !!!

;(define (next-boards bd) empty)   ;stub

(define (next-boards p)
  (apply-jumps (pair-board p) 
               (make-valid-jumps (pair-board p))))

;; ==============
;; Board (listof Jump) -> (listof Pair)
;; apply jumps to board and compound a jump
;;    and its corresponding board to produce a list of pairs
;; ASSUME: the jumps are valid
(check-expect (apply-jumps B0 (list J1 J2))
              (list (make-pair B01 J1)
                    (make-pair B02 J2)))

; (define (apply-jumps bd loj) empty)  ;stub

(define (apply-jumps bd loj)
  (cond [(empty? loj) empty]
        [else
         (cons (make-pair (apply-jump bd (first loj))
                          (first loj))
               (apply-jumps bd (rest loj)))]))

;; ==============
;; Board Jump -> Board                                                              !!!Try to combine apply-jump and apply-jumps
;; apply a jump to the consumed board to produce a new board
;; ASSUME: the jump is valid
(check-expect (apply-jump B0 J1) B01)

;(define (apply-jump bd j) B0)   ;stub

(define (apply-jump bd j)
  (cond [(empty? bd) empty]
        [(= (jump-from j)
            (find-pos bd))
         (cons T
               (apply-jump (rest bd) j))]
        [(= (jump-over j)
            (find-pos bd))
         (cons T 
               (apply-jump (rest bd) j))]
        [(= (jump-to j)
            (find-pos bd))
         (cons F
               (apply-jump (rest bd) j))]
        [else
         (cons (first bd)
               (apply-jump (rest bd) j))]))

;; ==============
;; (listof Boolean) -> Position
;; given a list of booleans that has been cut off from the front,                      !!!Paraphrase!!!
;;    produces the position of (first bd)
(check-expect (find-pos B0) 0)
(check-expect (find-pos (list true true false)) 12)

;(define (find-pos bd) 0)  ;stub

(define (find-pos bd)
  (cond [(empty? bd) 15]
        [else
         (+ -1 (find-pos (rest bd)))]))

;; ==============
;; Board -> (listof Jump)
;; produces a list of jumps that are valid on the consumed board
(check-expect (make-valid-jumps B4) empty)
(check-expect (make-valid-jumps B0)
              (list J2 J1))
(check-expect (make-valid-jumps B3)
              (list J3 J1))
(check-expect (make-valid-jumps B1)
              (list
               (make-jump 1 4 8)
               (make-jump 3 7 12)
               (make-jump 6 7 8)
               (make-jump 7 4 2)
               (make-jump 9 5 2)
               (make-jump 10 11 12)
               (make-jump 14 13 12)))

;(define (make-valid-jumps bd) empty)   ;stub

(define (make-valid-jumps bd)
  (local [(define (valid-jump? j)
            ;; Jump -> Boolean 
            (and (false? (determine-state bd (jump-from j)))
                 (false? (determine-state bd (jump-over j)))
                 (not (false? (determine-state bd (jump-to j))))))]
    (filter valid-jump? JUMPS)))

;; ==============
;; Board Position -> Boolean 
;; produces the state (false/true) of a board at a given pos
(check-expect (determine-state B0 0) true)
(check-expect (determine-state B0 8) false)
(check-expect (determine-state B1 3) false)

;(define (determine-state bd pos) false)   ;stub

(define (determine-state bd pos)
  (local [(define base (- pos 1))]
    (if (= base -1) 
        (first bd)
        (determine-state (rest bd)(sub1 pos)))))

;; ==============
;; (listof Pair) -> (listof Jump)
;; produces a list of jumps from a list of pairs with J0 removed

(check-expect (produce-steps (list
                              (make-pair (list true false false false false false false false false false false false false false false) (make-jump 0 0 0))
                              (make-pair (list false true false true false false false false false false false false false false false) (make-jump 3 1 0))
                              (make-pair (list false true false false true true false false false false false false false false false) (make-jump 5 4 3))
                              (make-pair (list true true true false true false false false false false false false false false false) (make-jump 0 2 5))
                              (make-pair (list true false true true true false true false false false false false false false false) (make-jump 6 3 1))
                              (make-pair (list true false false true true true true false false true false false false false false) (make-jump 9 5 2))
                              (make-pair (list true false false true false true true true false true false true false false false) (make-jump 11 7 4))
                              (make-pair (list true false false true false false true true true true false true true false false) (make-jump 12 8 5))
                              (make-pair (list true true false true true false true true false true false true true false false) (make-jump 1 4 8))
                              (make-pair (list true true true true true true true true false false false true true false false) (make-jump 2 5 9))
                              (make-pair (list true true true true true false true true false true false true true false true) (make-jump 14 9 5))
                              (make-pair (list true true true true true true true true true true false true false false true) (make-jump 5 8 12))
                              (make-pair (list true true true true true true true true true true false false true true true) (make-jump 13 12 11))
                              (make-pair (list true true true true true true true true true true true true false true true) (make-jump 10 11 12))))
              (list
               (make-jump 3 1 0)
               (make-jump 5 4 3)
               (make-jump 0 2 5)
               (make-jump 6 3 1)
               (make-jump 9 5 2)
               (make-jump 11 7 4)
               (make-jump 12 8 5)
               (make-jump 1 4 8)
               (make-jump 2 5 9)
               (make-jump 14 9 5)
               (make-jump 5 8 12)
               (make-jump 13 12 11)
               (make-jump 10 11 12)))

;(define (produce-steps lop) JUMPS)  ;stub

(define (produce-steps lop)
  (remove J0 (map pair-jump lop)))
;; ===============================
;; ===============================
(solve B2)