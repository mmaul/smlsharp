signature STREAM =
sig
  type 'xa stream
  val streamify : (unit -> '_a) -> '_a stream
  val cons : '_a * '_a stream -> '_a stream
  val get : '_a stream -> '_a * '_a stream
end;
