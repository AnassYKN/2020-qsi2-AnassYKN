open Framework;
open QCheckRely;
open Generator.Fantasy;
open Lib.Troll;


let {describe} = extendDescribe(QCheckRely.Matchers.matchers);

describe("Troll Invariance", ({test}) => {
  test("Troll score should be 0 when all elves resurrected", ({expect}) => {
    QCheck.Test.make(
      ~count=1000,
      ~name="Troll score should be 0 when all elves resurrected",
      troll_arbitrary,
      troll =>
      all_elves_resurrected(troll) |> scoring == 0
    )
    |> expect.ext.qCheckTest;
    ();
  });
  test("Troll score should always be >= 0", ({expect}) => {
    QCheck.Test.make(
      ~count=1000,
      ~name="Troll score should always be >= 0",
      troll_arbitrary,
      troll =>
      scoring(troll) >= 0
    )
    |> expect.ext.qCheckTest;
    ()
  });
});

describe("Troll Inverse", ({test}) => {
  test("oops_he_survived should always be inverse of i_got_one", ({expect}) => {
    QCheck.Test.make(
      ~count=1000,
      ~name="Troll score should be 0 when all elves resurrected",
      troll_elf_arbitrary,
      ((troll,elf)) =>
      i_got_one(elf,troll) |> oops_he_survived(elf) |> scoring == scoring(troll)
    )
    |> expect.ext.qCheckTest;
    ()
  })
});

describe("Troll Analogy", ({test}) => {
  test("i_got_one and i_got should be consistent", ({expect}) => {
    QCheck.Test.make(
      ~count=1000,
      ~name="i_got_one and i_got should be consistent",
      troll_elf_int_arbitrary,
      ((troll,elf,nbr)) => {
        let trollScore = ref(troll);
          for(i in 1 to nbr){
            trollScore := i_got_one(elf,trollScore^);
          };
          (trollScore^ |> scoring ) == (i_got(nbr,elf,troll) |> scoring )
        }
    )
    |> expect.ext.qCheckTest;
    ()
  })
});

describe("Troll Idempotence", ({test}) => {
  test(
    "all_elves_of_a_kind_resurrected brings the Troll killing list to a stable state",
    ({expect}) => {
    /* Test go there */
    ()
  })
});