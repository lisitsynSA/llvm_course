; ModuleID = 'top'
source_filename = "top"

declare void @llvm.sim.putpixel(i32, i32, i32)

declare void @llvm.sim.flush()

define void @app() {
entry:
  %0 = alloca i32, align 4
  %1 = getelementptr i32, ptr %0, i32 0
  store i32 0, ptr %1, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  br label %loopStep

loopStep:                                         ; preds = %loopY_end, %entry
  %4 = getelementptr i32, ptr %3, i32 0
  store i32 0, ptr %4, align 4
  %5 = getelementptr i32, ptr %0, i32 0
  %6 = load i32, ptr %5, align 4
  %7 = icmp ne i32 %6, 1000
  %8 = zext i1 %7 to i32
  %9 = icmp ne i32 %8, 0
  br i1 %9, label %loopY, label %loopStep_end

loopY:                                            ; preds = %loopX_end, %loopStep
  %10 = getelementptr i32, ptr %2, i32 0
  store i32 0, ptr %10, align 4
  %11 = getelementptr i32, ptr %3, i32 0
  %12 = load i32, ptr %11, align 4
  %13 = icmp ne i32 %12, 256
  %14 = zext i1 %13 to i32
  %15 = icmp ne i32 %14, 0
  br i1 %15, label %loopX, label %loopY_end

loopStep_end:                                     ; preds = %loopStep
  ret void

loopX:                                            ; preds = %iterX, %loopY
  %16 = getelementptr i32, ptr %2, i32 0
  %17 = load i32, ptr %16, align 4
  %18 = icmp ne i32 %17, 512
  %19 = zext i1 %18 to i32
  %20 = icmp ne i32 %19, 0
  br i1 %20, label %iterX, label %loopX_end

loopY_end:                                        ; preds = %loopY
  %21 = getelementptr i32, ptr %0, i32 0
  %22 = getelementptr i32, ptr %0, i32 0
  %23 = load i32, ptr %22, align 4
  %24 = add i32 %23, 1
  store i32 %24, ptr %21, align 4
  call void @llvm.sim.flush()
  br label %loopStep

iterX:                                            ; preds = %loopX
  %25 = getelementptr i32, ptr %2, i32 0
  %26 = load i32, ptr %25, align 4
  %27 = getelementptr i32, ptr %3, i32 0
  %28 = load i32, ptr %27, align 4
  %29 = getelementptr i32, ptr %2, i32 0
  %30 = load i32, ptr %29, align 4
  %31 = getelementptr i32, ptr %3, i32 0
  %32 = load i32, ptr %31, align 4
  %33 = mul i32 %30, %32
  %34 = getelementptr i32, ptr %0, i32 0
  %35 = load i32, ptr %34, align 4
  %36 = mul i32 %33, %35
  %37 = sub i32 %36, 16777216
  call void @llvm.sim.putpixel(i32 %26, i32 %28, i32 %37)
  %38 = getelementptr i32, ptr %2, i32 0
  %39 = getelementptr i32, ptr %2, i32 0
  %40 = load i32, ptr %39, align 4
  %41 = add i32 %40, 1
  store i32 %41, ptr %38, align 4
  br label %loopX

loopX_end:                                        ; preds = %loopX
  %42 = getelementptr i32, ptr %3, i32 0
  %43 = getelementptr i32, ptr %3, i32 0
  %44 = load i32, ptr %43, align 4
  %45 = add i32 %44, 1
  store i32 %45, ptr %42, align 4
  br label %loopY
}
