mutex mut;
mutex read_mut;
idx = 100;
buf1[100], buf2[100];
write_buf = buf1
read_buf = buf2;
cond_var cond;

get_ids() {
	while (1) {
		mut.lock();
		while (go == 0) {
			wait(cond, mut);
		}
		write(write_buf); //1s
		go = 0;
		mut.unlock();
	}
}

get_one_id()
{
	id;
	read_mut.lock();
	if (idx == 100) {
		//done with read_buf
		//swap
		tmp = write_buf;
		write_buf = read_buf;
		read_buf = write_buf;
		idx = 0;
		mut.lock();
		go = 1;
		signal(cond);
		mut.unlock();
	} else {
		id = read_buf[idx];
		idx++;
	}
	read_mut.unlock();
	return id;
}
