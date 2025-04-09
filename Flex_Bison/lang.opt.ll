; ModuleID = 'lang.ll'
source_filename = "top"

declare void @llvm.sim.putpixel(i32, i32, i32)

declare void @llvm.sim.flush()

define void @app() local_unnamed_addr {
entry:
  br label %loopY.preheader

loopY.preheader:                                  ; preds = %entry, %loopY_end
  %.01217 = phi i32 [ 0, %entry ], [ %1, %loopY_end ]
  br label %loopX.preheader

loopX.preheader:                                  ; preds = %loopY.preheader, %loopX_end
  %.016 = phi i32 [ 0, %loopY.preheader ], [ %5, %loopX_end ]
  %0 = mul nuw nsw i32 %.016, %.01217
  br label %iterX

loopStep_end:                                     ; preds = %loopY_end
  ret void

loopY_end:                                        ; preds = %loopX_end
  %1 = add nuw nsw i32 %.01217, 1
  tail call void @llvm.sim.flush()
  %.not = icmp eq i32 %1, 1000
  br i1 %.not, label %loopStep_end, label %loopY.preheader

iterX:                                            ; preds = %loopX.preheader, %iterX
  %.01115 = phi i32 [ 0, %loopX.preheader ], [ %4, %iterX ]
  %2 = mul nuw nsw i32 %0, %.01115
  %3 = add nsw i32 %2, -16777216
  tail call void @llvm.sim.putpixel(i32 %.01115, i32 %.016, i32 %3)
  %4 = add nuw nsw i32 %.01115, 1
  %.not14 = icmp eq i32 %4, 512
  br i1 %.not14, label %loopX_end, label %iterX

loopX_end:                                        ; preds = %iterX
  %5 = add nuw nsw i32 %.016, 1
  %.not13 = icmp eq i32 %5, 256
  br i1 %.not13, label %loopY_end, label %loopX.preheader
}
