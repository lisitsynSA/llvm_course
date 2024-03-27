define dso_local void @app() local_unnamed_addr {
  br label %1

1:                                                ; preds = %0, %7
  %2 = phi i32 [ 0, %0 ], [ %8, %7 ]
  br label %4

3:                                                ; preds = %7
  ret void

4:                                                ; preds = %1, %10
  %5 = phi i32 [ 0, %1 ], [ %11, %10 ]
  %6 = mul nuw nsw i32 %5, %2
  br label %13

7:                                                ; preds = %10
  tail call void (...) @simFlush()
  %8 = add nuw nsw i32 %2, 1
  %9 = icmp eq i32 %8, 1000
  br i1 %9, label %3, label %1

10:                                               ; preds = %13
  %11 = add nuw nsw i32 %5, 1
  %12 = icmp eq i32 %11, 256
  br i1 %12, label %7, label %4

13:                                               ; preds = %4, %13
  %14 = phi i32 [ 0, %4 ], [ %17, %13 ]
  %15 = mul nuw nsw i32 %6, %14
  %16 = add nsw i32 %15, -16777216
  tail call void @simPutPixel(i32 noundef %14, i32 noundef %5, i32 noundef %16)
  %17 = add nuw nsw i32 %14, 1
  %18 = icmp eq i32 %17, 512
  br i1 %18, label %10, label %13
}

declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr

declare void @simFlush(...) local_unnamed_addr
