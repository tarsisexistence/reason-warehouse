[@react.component]
let make = (~children) => {
  <div
    className="container"
    style={ReactDOMRe.Style.make(
      ~color="var(--textNormal)",
      ~background="var(--bg)",
      ~transition="color 0.2s ease-out, background 0.2s ease-out",
      ~minHeight="100vh",
      (),
    )}>
    <main
      className="content"
      style={ReactDOMRe.Style.make(
        ~marginLeft="auto",
        ~marginRight="auto",
        ~maxWidth="42rem",
        ~padding="2.625rem 1.3125rem",
        (),
      )}>
      children
    </main>
  </div>;
};