#define iterstart@Range cellmin

iterfunc Range(cur, min, max, step = 1)
{
	if (cur == -1) return min;
	cur += step;
	return (min <= cur < max) ? cur : -1;
}

