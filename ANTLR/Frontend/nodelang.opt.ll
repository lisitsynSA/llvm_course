; ModuleID = 'nodelang.ll'
source_filename = "top"

declare void @llvm.sim.putpixel(i32, i32, i32)

define noundef i32 @PUT_PIXEL(i32 %0, i32 %1, i32 %2) local_unnamed_addr {
entry:
  tail call void @llvm.sim.putpixel(i32 %0, i32 %1, i32 %2)
  ret i32 0
}

declare void @llvm.sim.flush()

define noundef i32 @FLUSH() local_unnamed_addr {
entry:
  tail call void @llvm.sim.flush()
  ret i32 0
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind willreturn memory(none)
define i32 @color(i32 %0, i32 %1, i32 %2) local_unnamed_addr #0 {
entry:
  %3 = mul i32 %1, %0
  %4 = mul i32 %3, %2
  %5 = add i32 %4, -16777216
  ret i32 %5
}

define noundef i32 @app() local_unnamed_addr {
entry:
  br label %.preheader2

.preheader2:                                      ; preds = %entry, %4
  %0 = phi i32 [ 0, %entry ], [ %5, %4 ]
  br label %.preheader

1:                                                ; preds = %4
  ret i32 42

.preheader:                                       ; preds = %.preheader2, %13
  %2 = phi i32 [ 0, %.preheader2 ], [ %14, %13 ]
  %3 = mul nuw nsw i32 %2, %0
  br label %7

4:                                                ; preds = %13
  tail call void @llvm.sim.flush()
  %5 = add nuw nsw i32 %0, 1
  %6 = icmp eq i32 %5, 42
  br i1 %6, label %1, label %.preheader2

7:                                                ; preds = %.preheader, %7
  %8 = phi i32 [ 0, %.preheader ], [ %11, %7 ]
  %9 = mul nuw nsw i32 %3, %8
  %10 = add nuw nsw i32 %9, -16777216
  tail call void @llvm.sim.putpixel(i32 %8, i32 %2, i32 %10)
  %11 = add nuw nsw i32 %8, 1
  %12 = icmp eq i32 %11, 512
  br i1 %12, label %13, label %7

13:                                               ; preds = %7
  %14 = add nuw nsw i32 %2, 1
  %15 = icmp eq i32 %14, 256
  br i1 %15, label %4, label %.preheader
}

attributes #0 = { mustprogress nofree norecurse nosync nounwind willreturn memory(none) }
