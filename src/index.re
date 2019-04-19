type frame =
  | Strike
  | Spare(int)
  | Bad(int, int);

let score = [
  Strike,
  Strike,
  Strike,
  Strike,
  Strike,
  Strike,
  Strike,
  Strike,
  Strike,
  Strike,
  Strike,
  Strike,
];

let score_next_one = frame =>
  switch (frame) {
  | Bad(first, _second) => first
  | Spare(first) => first
  | Strike => 10
  };

let score_next_two = (frame1, frame2) =>
  switch (frame1) {
  | Bad(first, second) => first + second
  | Spare(_) => 10
  | Strike => 10 + score_next_one(frame2)
  };

let rec calc = frames =>
  switch (frames) {
  | [Bad(a, b), ...rest] => a + b + calc(rest)
  | [Strike, a, b] => 10 + score_next_two(a, b)
  | [Strike, a, b, ...rest] =>
    10 + score_next_two(a, b) + calc([a, b, ...rest])
  | [Spare(_), a] => 10 + score_next_one(a)
  | [Spare(_), a, ...rest] => 10 + score_next_one(a) + calc([a, ...rest])
  | [] => 0
  };

Js.log(calc(score));
