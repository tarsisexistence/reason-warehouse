[@react.component]
let make = (~article: Types.article) => {
  let href = "articles/" ++ article.id;

  <article
    style={ReactDOMRe.Style.make(~display="block", ~padding="30px 0", ())}>
    <a
      href
      onClick={event => {
        ReactEvent.Mouse.preventDefault(event);
        ReasonReactRouter.push(href);
      }}
      style={ReactDOMRe.Style.make(
        ~fontSize="1.75rem",
        ~fontWeight="700",
        ~marginBottom="0.4375rem",
        ~boxShadow="none",
        ~display="block",
        (),
      )}>
      {article.title |> React.string}
    </a>
    <small style={ReactDOMRe.Style.make(~fontSize="80%", ())}>
      {article |> Utils.Common.getTimeDescription |> React.string}
    </small>
    <p> {"Let clean code guide you. Then let it go" |> React.string} </p>
  </article>;
};