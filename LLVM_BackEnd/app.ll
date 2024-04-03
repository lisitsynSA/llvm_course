define dso_local void @app() local_unnamed_addr {
entry:
  br label %for.cond1.preheader

for.cond1.preheader:                              ; preds = %entry, %for.cond.cleanup3
  %step.026 = phi i32 [ 0, %entry ], [ %inc14, %for.cond.cleanup3 ]
  br label %for.cond5.preheader

for.cond.cleanup:                                 ; preds = %for.cond.cleanup3
  ret void

for.cond5.preheader:                              ; preds = %for.cond1.preheader, %for.cond.cleanup7
  %y.025 = phi i32 [ 0, %for.cond1.preheader ], [ %inc11, %for.cond.cleanup7 ]
  %mul = mul nuw nsw i32 %y.025, %step.026
  br label %for.body8

for.cond.cleanup3:                                ; preds = %for.cond.cleanup7
  tail call void @llvm.sim.flush()
  %inc14 = add nuw nsw i32 %step.026, 1
  %exitcond28.not = icmp eq i32 %inc14, 1000
  br i1 %exitcond28.not, label %for.cond.cleanup, label %for.cond1.preheader

for.cond.cleanup7:                                ; preds = %for.body8
  %inc11 = add nuw nsw i32 %y.025, 1
  %exitcond27.not = icmp eq i32 %inc11, 256
  br i1 %exitcond27.not, label %for.cond.cleanup3, label %for.cond5.preheader

for.body8:                                        ; preds = %for.cond5.preheader, %for.body8
  %x.024 = phi i32 [ 0, %for.cond5.preheader ], [ %inc, %for.body8 ]
  %mul9 = mul nuw nsw i32 %mul, %x.024
  %add = add nsw i32 %mul9, -16777216
  tail call void @llvm.sim.putpixel(i32 %x.024, i32 %y.025, i32 %add)
  %inc = add nuw nsw i32 %x.024, 1
  %exitcond.not = icmp eq i32 %inc, 512
  br i1 %exitcond.not, label %for.cond.cleanup7, label %for.body8
}

declare void @llvm.sim.putpixel(i32, i32, i32)

declare void @llvm.sim.flush()
