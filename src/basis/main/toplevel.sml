(**
 * toplevel bindings
 * @author UENO Katsuhiro
 * @author YAMATODANI Kiyoshi
 * @copyright 2010, 2011, 2012, 2013, Tohoku University.
 *)

type substring = Substring.substring
datatype order = datatype General.order

exception Empty = List.Empty
exception Option = Option.Option
exception Span = General.Span

val op @ = List.@
val op ^ = String.^
val app = List.app
val ceil = Real64.ceil
val chr = Char.chr
val concat = String.concat
val exnMessage = General.exnMessage
val exnName = General.exnName
val explode = String.explode
val floor = Real64.floor
val foldl = List.foldl
val foldr = List.foldr
val getOpt = Option.getOpt
val hd = List.hd
val implode = String.implode
val isSome = Option.isSome
val length = List.length
val map = List.map
val not = Bool.not
val null = List.null
val ord = Char.ord
val print = TextIO.print
val real = Real64.fromInt
val rev = List.rev
val round = Real64.round
val size = String.size
val str = String.str
val substring = String.substring
val tl = List.tl
val trunc = Real64.trunc
val valOf = Option.valOf
val vector = Vector.fromList
