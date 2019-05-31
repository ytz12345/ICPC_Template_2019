#本题答案的分母不超过1e9，给定小数的小数点位为18位
inf, inff = 10 ** 9, 10 ** 18
for i in range(int(input())):
	n = int(input()[2:])
	if n == 0: print('0 1')
	else:
		lp, lq, rp, rq = 0, 1, 1, 1
		while max(lq, rq) <= inf:
			mp, mq = lp + rp, lq + rq
			if mp * inff <= mq * n: 
				l, r, mid, cnt = 1, (inf - lq) // rq + 1, -1, -1
				while l <= r:
					mid = l + r >> 1
					if (lp + rp * mid) * inff <= (lq + rq * mid) * n:
						cnt, l = mid, mid + 1
					else:
						r = mid - 1
				lp, lq = lp + rp * cnt, lq + rq * cnt 
			else: 
				l, r, mid, cnt = 1, (inf - rq) // lq + 1, -1, -1
				while l <= r:
					mid = l + r >> 1
					if (rp + lp * mid) * inff > (rq + lq * mid) * n:
						cnt, l = mid, mid + 1
					else:
						r = mid - 1
				rp, rq = rp + lp * cnt, rq + lq * cnt 
		if lq <= inf: print(lp, lq)
		else: print(rp, rq)