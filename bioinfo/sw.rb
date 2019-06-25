class Smithwater

	def initialize(gap = -4, mismatch = -3, matchp = 5)
		@gap = gap
		@mismatch = mismatch
		@matchp = matchp
	end

	def setSeqA(seqa = "")
		@seqa = seqa
	end

	def setSeqB(seqb = "")
		@seqb = seqb
	end

	def align()
		
	end

end

a = Smithwater.new