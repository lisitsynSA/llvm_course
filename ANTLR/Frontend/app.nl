(NODE alfa 16777216)
(NODE color (x y step)
    (- (* step (*x y)) alfa)
)
(NODE app ()
    (NODE step_size 42)
    (LOOP step 0 step_size
        (LOOP y 0 SIM_Y_SIZE
            (LOOP x 0 SIM_X_SIZE
                (PUT_PIXEL x y (color x y step))
            )
        )
        (FLUSH)
    )
)