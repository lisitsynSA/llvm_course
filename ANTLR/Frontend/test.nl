(NODE alfa 16777216)

(NODE color (x y step)
    (- (* step (*x y)) alfa)
)

(NODE loop_test ()
    (LOOP i 0 10
    )
)

(NODE call_loop_test ()
    (LOOP i 0 10
        (loop_test)
    )
)

(NODE app ()
    (PUT_PIXEL (/ X_SIZE 2) (/ Y_SIZE 2) -1)
    (FLUSH)
)
