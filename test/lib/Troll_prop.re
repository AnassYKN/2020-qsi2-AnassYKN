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
  test("all_elves_of_a_kind_resurrected brings the Troll killing list to a stable state",({expect}) => {
      QCheck.Test.make(
        ~count=1000,
        ~name="all_elves_of_a_kind_resurrected brings the Troll killing list to a stable state",
        troll_elf_arbitrary,
        ((troll, elf)) => {
            (scoring(all_elves_resurrected(troll))) == (scoring((all_elves_of_a_kind_resurrected(elf,troll))))
          }
      )
      |> expect.ext.qCheckTest;
    ()
  })
});

describe("Troll Metamophism", ({test}) => {
  test("Verify that the execution of a function with variants of the same input must lead to equal outputs",({expect}) => {
      QCheck.Test.make(
        ~count=1000,
        ~name="Verify that the execution of a function with variants of the same input must lead to equal outputs",
        troll_elf_arbitrary,
        ((troll, elf)) => {
          scoring(troll) <= scoring(i_got_one(elf, troll));
        }
      ) |> expect.ext.qCheckTest;
      ();
  })
});


describe("Troll Injection", ({test}) => {
  test("check the diffrent inputs lead to different outputs",({expect}) => {
    QCheck.Test.make(
      ~count=1000,
      ~name="check the diffrent inputs lead to different outputs",
      troll_two_elves_arbitrary,
      ((troll, elf_X, elf_Y)) =>
      {
        if( elf_X == elf_Y){i_got_one(elf_X, troll) == i_got_one(elf_Y, troll);}
        else {              i_got_one(elf_X, troll) != i_got_one(elf_Y, troll);}
      }
    )
    |> expect.ext.qCheckTest;
    ();
  })
});