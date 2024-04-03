define dso_local void @app() {
entry:
  call void @llvm.sim.putpixel(i32 5, i32 5, i32 -1)
  call void @llvm.sim.flush()
  ret void
}

declare void @llvm.sim.putpixel(i32, i32, i32)

declare void @llvm.sim.flush()
