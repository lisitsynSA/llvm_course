; ModuleID = 'top'
source_filename = "top"

declare void @llvm.sim.putpixel(i32, i32, i32)

define i32 @PUT_PIXEL(i32 %0, i32 %1, i32 %2) {
entry:
  call void @llvm.sim.putpixel(i32 %0, i32 %1, i32 %2)
  ret i32 0
}

declare void @llvm.sim.flush()

define i32 @FLUSH() {
entry:
  call void @llvm.sim.flush()
  ret i32 0
}

define i32 @color(i32 %0, i32 %1, i32 %2) {
entry:
  %3 = mul i32 %0, %1
  %4 = mul i32 %2, %3
  %5 = sub i32 %4, 16777216
  ret i32 %5
}

define i32 @app() {
entry:
  br label %0

0:                                                ; preds = %9, %entry
  %1 = phi i32 [ 0, %entry ], [ %11, %9 ]
  %2 = icmp eq i32 %1, 42
  br i1 %2, label %4, label %3

3:                                                ; preds = %0
  br label %5

4:                                                ; preds = %0
  ret i32 %1

5:                                                ; preds = %19, %3
  %6 = phi i32 [ 0, %3 ], [ %20, %19 ]
  %7 = icmp eq i32 %6, 256
  br i1 %7, label %9, label %8

8:                                                ; preds = %5
  br label %12

9:                                                ; preds = %5
  %10 = call i32 @FLUSH()
  %11 = add i32 %1, 1
  br label %0

12:                                               ; preds = %15, %8
  %13 = phi i32 [ 0, %8 ], [ %18, %15 ]
  %14 = icmp eq i32 %13, 512
  br i1 %14, label %19, label %15

15:                                               ; preds = %12
  %16 = call i32 @color(i32 %13, i32 %6, i32 %1)
  %17 = call i32 @PUT_PIXEL(i32 %13, i32 %6, i32 %16)
  %18 = add i32 %13, 1
  br label %12

19:                                               ; preds = %12
  %20 = add i32 %6, 1
  br label %5
}
