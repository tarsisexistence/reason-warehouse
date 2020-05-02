let title = "Reason / Erland Blog";

let updateTitle: _ => unit = [%bs.raw
  {|
  function updateTitle() {
    document.title = "⏰ " + title + " ⏰";
  }|}
];

updateTitle();

[@react.component]
let make = () =>
  <section
    style={ReactDOMRe.Style.make(
      ~display="flex",
      ~justifyContent="space-between",
      ~alignItems="center",
      ~marginBottom="2.625rem",
      (),
    )}>
    <h1
      style={ReactDOMRe.Style.make(
        ~fontSize="1.98818rem",
        ~lineHeight="2.625rem",
        ~marginTop="0",
        ~marginBottom="0",
        (),
      )}>
      <a
        style={ReactDOMRe.Style.make(
          ~boxShadow="none",
          ~textDecoration="none",
          ~color="var(--textTitle)",
          (),
        )}>
        {React.string(title)}
      </a>
    </h1>
  </section>;