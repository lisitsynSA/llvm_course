(NODE alfa 16777216)
(NODE color (x y step)
    (- (* step (*x y)) alfa)
)
(NODE app ()
    (NODE steps 42)
    (LOOP step 0 steps
        (LOOP y 0 Y_SIZE
            (LOOP x 0 X_SIZE
                (PUT_PIXEL x y (color x y step))
            )
        )
        (FLUSH)
    )
)
