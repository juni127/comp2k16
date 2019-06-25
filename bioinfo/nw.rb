class Needlewunsch

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

	def initMatrix()
		a = @seqa.length
		b = @seqb.length

		# Precisa dessa linha?
		@matrix = Hash.new(0)

		for i in 0..a do
			@matrix[[i, 0]]= @gap * i
		end

		for j in 0..b do
			@matrix[[0, j]]= @gap * j
		end

	end

	def max(a, b, c)
		return [a, b, c].max
	end

	def fillMatrix()
		a = @seqa.length
		b = @seqb.length

		for i in 1..a do
			for j in 1..b do
				@seqa[i-1] == @seqb[j-1] ? (x = @matrix[[i-1, j-1]] + @matchp) : (x = @matrix[[i-1, j-1]] + @mismatch)
				y = @matrix[[i, j-1]] + @gap
				z = @matrix[[i-1, j]] + @gap
				@matrix[[i, j]] = self.max(x, y, z)
			end
		end

	end

	def traceback()

		i = @seqa.length
		j = @seqb.length

		@resa = Array.new(0)
		@resb = Array.new(0)

		begin
			if(@matrix[[i-1, j-1]] > @matrix[[i, j-1]] && @matrix[[i-1, j-1]] > @matrix[[i-1, j]])
				i -= 1
				j -= 1
				@resa.push(@seqa[i])
				@resb.push(@seqb[j])
			elsif(@matrix[[i, j-1]] > @matrix[[i-1, j-1]] && @matrix[[i, j-1]] > @matrix[[i-1, j]])
				j -= 1
				@resa.push('-')
				@resb.push(@seqb[j])
			else
				i -= 1
				@resa.push(@seqa[i])
				@resb.push('-')
			end
		end while(i != 0 && j != 0) 

		@resa = @resa.reverse
		@resb = @resb.reverse
	end

	def printAlignment()
		print(@resa)
		puts("")
		print(@resb)
		puts("")
	end

	def printMatrix()
		a = @seqa.length
		b = @seqb.length

		for i in 0..a do
			for j in 0..b do
				print(@matrix[[i, j]])
				print(", ")
			end
			puts("")
		end
	end

	def align()
		self.initMatrix()
		self.fillMatrix()
		self.traceback()
	end

end

algoritmo = Needlewunsch.new

algoritmo.setSeqA("TACCCG")
algoritmo.setSeqB("ATCCG")

algoritmo.align()
algoritmo.printAlignment()